#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

float Screenwidth = 1920.f;
float Screenheight = 1080.f;
sf::RenderWindow window(sf::VideoMode(Screenwidth, Screenheight), "Pong! :)");
sf::View Mainview(sf::FloatRect(0, 0, 1920, 1080));

sf::RectangleShape Ball;
sf::RectangleShape RightPaddle;
sf::RectangleShape LeftPaddle;
sf::Font Montserrat;

bool PauseGame = false;

int main() {
    sf::Clock clock;

    Ball.setSize(sf::Vector2f(40, 40));
    Ball.setOrigin(sf::Vector2f(20, 20));
    Ball.setPosition(960, 540);

    sf::Vector2f dir(450.f, 450.f);

    LeftPaddle.setSize(sf::Vector2f(30, 200));
    LeftPaddle.setOrigin(sf::Vector2f(15, 100));
    LeftPaddle.setPosition(40, 540);

    float BallCountdown = 3;

    Montserrat.loadFromFile("Pong/Montserrat-Regular.ttf");

    sf::Text countdown;

    countdown.setFont(Montserrat);
    countdown.setCharacterSize(192);
    countdown.setString("1");
    countdown.setOrigin(countdown.getLocalBounds().left + countdown.getLocalBounds().width / 2, countdown.getLocalBounds().top + countdown.getLocalBounds().height / 2);
    countdown.setPosition(Screenwidth / 2, Screenheight / 2);

    window.setKeyRepeatEnabled(false);

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        BallCountdown -= elapsed.asSeconds();

        float ScreenRatio = Screenwidth / Screenheight;
        Mainview.setViewport(sf::FloatRect((1.f - (window.getSize().y * ScreenRatio) / (window.getSize().x * 1.f)) / 2, (1.f - (window.getSize().x * 1.f) / (window.getSize().y * ScreenRatio)) / 2, (window.getSize().y * ScreenRatio) / (window.getSize().x * 1.f), (window.getSize().x * 1.f) / (window.getSize().y * ScreenRatio)));
        if (Mainview.getViewport().top * 2 > Mainview.getViewport().left * 2) {
            Mainview.setSize(sf::Vector2f(Screenwidth / (1 - Mainview.getViewport().top * 2), Screenheight));
        } else {
            Mainview.setSize(sf::Vector2f(Screenwidth, Screenheight / (1 - Mainview.getViewport().left * 2)));   
        }
        window.setView(Mainview);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (LeftPaddle.getPosition().y > 100.f) {
                LeftPaddle.move(0.f, -500.f * elapsed.asSeconds());
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (LeftPaddle.getPosition().y < 980.f) {
                LeftPaddle.move(0.f, 500.f * elapsed.asSeconds());
            }
        }

        if (Ball.getPosition().x + dir.x * elapsed.asSeconds() > Screenwidth - 20) {
            dir = sf::Vector2f(-dir.x, dir.y);
        } 
        if (Ball.getPosition().x + dir.x * elapsed.asSeconds() < -20) {
            BallCountdown = 3;
            Ball.setPosition(Screenwidth / 2, Screenheight / 2);
            dir = sf::Vector2f(450.f, 450.f);
        } 
        if (Ball.getPosition().y + dir.y * elapsed.asSeconds() > Screenheight - 20 || Ball.getPosition().y + dir.y * elapsed.asSeconds() < 20) {
            dir = sf::Vector2f(dir.x, -dir.y);
        }

        sf::FloatRect BallPlusMove(Ball.getGlobalBounds().left + dir.x * elapsed.asSeconds(), Ball.getGlobalBounds().top + dir.y * elapsed.asSeconds(), Ball.getGlobalBounds().width, Ball.getGlobalBounds().height);
        if (BallPlusMove.intersects(LeftPaddle.getGlobalBounds())) {
            dir = sf::Vector2f(-dir.x * 1.05f, dir.y * 1.05f);
            Ball.move(dir * 2.5f * elapsed.asSeconds());
        } 

        if (BallCountdown < 0 && PauseGame == false) {
            Ball.move(dir * elapsed.asSeconds());
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    PauseGame = !PauseGame;
                    BallCountdown = 3;
                }
            }
        }

        window.clear();

        window.draw(LeftPaddle);
        window.draw(RightPaddle);

        if (BallCountdown <= 0 || PauseGame == true) {
            window.draw(Ball);
        } 
        if (BallCountdown > 0 && PauseGame == false) {
            int BallCountdownCeil = std::ceil(BallCountdown);
            countdown.setString(std::to_string(BallCountdownCeil));
            window.draw(countdown);
        }

        if (PauseGame == true) {
            countdown.setString("ll");
            countdown.setScale(sf::Vector2f(2.f, 1.f));
            countdown.setLetterSpacing(-0.5f);
            window.draw(countdown);
        } else {
            countdown.setScale(sf::Vector2f(1.f, 1.f));
            countdown.setLetterSpacing(1);
        }

        window.display();
    }
}