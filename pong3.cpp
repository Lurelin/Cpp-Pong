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
sf::RectangleShape BorderRect;

bool PauseGame = false;
bool BallIntersectsLeftPaddle = false;
bool BallIntersectsRightPaddle = false;

sf::Vector2f dir(450.f, 450.f);
float AItargetpos = 810.f;
float AItimer = 0;

void AIMovement(float targetposition, float ElapsedTime) {
    std::cout << std::to_string(targetposition) << "\n";
    if (PauseGame == false) {
        if (RightPaddle.getPosition().y < targetposition && RightPaddle.getPosition().y < 980.f) {
            RightPaddle.move(sf::Vector2f(0.f, 500.f * ElapsedTime));
        } 
        if (RightPaddle.getPosition().y > targetposition && RightPaddle.getPosition().y > 100.f) {
            RightPaddle.move(sf::Vector2f(0.f, -500.f * ElapsedTime));
        }
    }
}

float AITargetPos(float ElapsedTime) {
    if (AItimer > 0.25) {
        sf::Vector2f AIdir = sf::Vector2f(dir.x / std::abs(dir.x) * 20.f, dir.y / std::abs(dir.y) * 20.f);
        sf::Vector2f Ballpos = Ball.getPosition();
        while (Ballpos.x < 1850 && Ballpos.x > 70) {
            if (Ballpos.y > Screenheight - 20 || Ballpos.y < 20) {
                AIdir = sf::Vector2f(AIdir.x, -AIdir.y);
            }
            Ballpos += AIdir;
        }
        AItargetpos = AIdir.x;
        AItimer = 0;
    } else {
        AItimer += ElapsedTime;
    }
    return AItargetpos;
}

int main() {
    sf::Clock clock;

    Ball.setSize(sf::Vector2f(40, 40));
    Ball.setOrigin(sf::Vector2f(20, 20));
    Ball.setPosition(960, 540);

    LeftPaddle.setSize(sf::Vector2f(30, 200));
    LeftPaddle.setOrigin(sf::Vector2f(15, 100));
    LeftPaddle.setPosition(40, 540);

    RightPaddle.setSize(sf::Vector2f(30, 200));
    RightPaddle.setOrigin(sf::Vector2f(15, 100));
    RightPaddle.setPosition(1880, 540);
    
    BorderRect.setSize(sf::Vector2f(Screenwidth - 16, Screenheight - 16));
    BorderRect.setOrigin(sf::Vector2f((Screenwidth - 16) / 2, (Screenheight - 16) / 2));
    BorderRect.setPosition(Screenwidth / 2, Screenheight / 2);
    BorderRect.setFillColor(sf::Color::Transparent);
    BorderRect.setOutlineColor(sf::Color::White);
    BorderRect.setOutlineThickness(8);

    float BallCountdown = 3;

    //For windows
    Montserrat.loadFromFile("C:/Users/alija/Documents/Cpp-Pong/Montserrat-Regular.ttf");
    //For Linux
    //Montserrat.loadFromFile("Cpp-Pong/Montserrat-Regular.ttf");

    sf::Text countdown;
    countdown.setFont(Montserrat);
    countdown.setCharacterSize(284);
    countdown.setString("1");
    countdown.setOrigin(countdown.getLocalBounds().left + countdown.getLocalBounds().width / 2, countdown.getLocalBounds().top + countdown.getLocalBounds().height / 2);
    countdown.setPosition(Screenwidth / 2, Screenheight / 2);

    sf::Text ScoreAI;
    ScoreAI.setFont(Montserrat);
    ScoreAI.setCharacterSize(192);
    ScoreAI.setString("0");
    ScoreAI.setOrigin(countdown.getLocalBounds().left + countdown.getLocalBounds().width / 2, countdown.getLocalBounds().top + countdown.getLocalBounds().height / 2);
    ScoreAI.setPosition(Screenwidth * 0.75f, Screenheight * 0.25f);

    sf::Text ScorePlayer;
    ScorePlayer.setFont(Montserrat);
    ScorePlayer.setCharacterSize(192);
    ScorePlayer.setString("0");
    ScorePlayer.setOrigin(countdown.getLocalBounds().left + countdown.getLocalBounds().width / 2, countdown.getLocalBounds().top + countdown.getLocalBounds().height / 2);
    ScorePlayer.setPosition(Screenwidth * 0.25f, Screenheight * 0.25f);

    int PlayerScore = 0;
    int AIScore = 0;

    window.setKeyRepeatEnabled(false);

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        if (PauseGame == false) {
            BallCountdown -= elapsed.asSeconds();
        }

        float ScreenRatio = Screenwidth / Screenheight;
        Mainview.setViewport(sf::FloatRect((1.f - (window.getSize().y * ScreenRatio) / (window.getSize().x * 1.f)) / 2, (1.f - (window.getSize().x * 1.f) / (window.getSize().y * ScreenRatio)) / 2, (window.getSize().y * ScreenRatio) / (window.getSize().x * 1.f), (window.getSize().x * 1.f) / (window.getSize().y * ScreenRatio)));
        if (Mainview.getViewport().top * 2 > Mainview.getViewport().left * 2) {
            Mainview.setSize(sf::Vector2f(Screenwidth / (1 - Mainview.getViewport().top * 2), Screenheight));
        } else {
            Mainview.setSize(sf::Vector2f(Screenwidth, Screenheight / (1 - Mainview.getViewport().left * 2)));   
        }
        window.setView(Mainview);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && PauseGame == false) {
            if (LeftPaddle.getPosition().y > 100.f) {
                LeftPaddle.move(0.f, -500.f * elapsed.asSeconds());
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && PauseGame == false) {
            if (LeftPaddle.getPosition().y < 980.f) {
                LeftPaddle.move(0.f, 500.f * elapsed.asSeconds());
            }
        }

        if (Ball.getPosition().x + dir.x * elapsed.asSeconds() > Screenwidth - 20) {
            PlayerScore++;
            BallCountdown = 3;
            Ball.setPosition(Screenwidth / 2, Screenheight / 2);
            dir = sf::Vector2f(450.f, 450.f);
        } 
        if (Ball.getPosition().x + dir.x * elapsed.asSeconds() < -20) {
            AIScore++;
            BallCountdown = 3;
            Ball.setPosition(Screenwidth / 2, Screenheight / 2);
            dir = sf::Vector2f(450.f, 450.f);
        } 
        if (Ball.getPosition().y + dir.y * elapsed.asSeconds() > Screenheight - 20 || Ball.getPosition().y + dir.y * elapsed.asSeconds() < 20) {
            dir = sf::Vector2f(dir.x, -dir.y);
        }

        sf::FloatRect BallPlusMove(Ball.getGlobalBounds().left + dir.x * elapsed.asSeconds(), Ball.getGlobalBounds().top + dir.y * elapsed.asSeconds(), Ball.getGlobalBounds().width, Ball.getGlobalBounds().height);
        if (!(BallPlusMove.intersects(LeftPaddle.getGlobalBounds())) && BallIntersectsLeftPaddle == true) {
            BallIntersectsLeftPaddle = false;
        }
        if (BallPlusMove.intersects(LeftPaddle.getGlobalBounds()) && BallIntersectsLeftPaddle == false) {
            BallIntersectsLeftPaddle = true;
            float Offset = 0.1 - std::abs(LeftPaddle.getPosition().y - (BallPlusMove.top + BallPlusMove.height / 2)) * 0.001f;
            //dir = sf::Vector2f(-dir.x * 1.05f, dir.y * 1.05f);
            dir = sf::Vector2f(-dir.x, dir.y);
            if (Offset < 0.05f) {
                dir.y = dir.y + dir.y * Offset * 4;
            } else {
                dir.x = dir.x + dir.x * Offset * 2;
            }
            //std::cout << std::to_string(dir.x) << "  " << std::to_string(dir.y) << "  " << std::to_string(Offset) << "\n";
            Ball.move(dir * elapsed.asSeconds());
        }

        if (!(BallPlusMove.intersects(RightPaddle.getGlobalBounds())) && BallIntersectsRightPaddle == true) {
            BallIntersectsRightPaddle = false;
        }
        if (BallPlusMove.intersects(RightPaddle.getGlobalBounds()) && BallIntersectsRightPaddle == false) {
            BallIntersectsRightPaddle = true;
            float Offset = 0.1 - std::abs(RightPaddle.getPosition().y - (BallPlusMove.top + BallPlusMove.height / 2)) * 0.001f;
            //dir = sf::Vector2f(-dir.x * 1.05f, dir.y * 1.05f);
            dir = sf::Vector2f(-dir.x, dir.y);
            if (Offset < 0.05f) {
                dir.y = dir.y + dir.y * Offset * 4;
            } else {
                dir.x = dir.x + dir.x * Offset * 2;
            }
            Ball.move(dir * elapsed.asSeconds());
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

        AIMovement(AITargetPos(elapsed.asSeconds()), elapsed.asSeconds());

        ScoreAI.setString(std::to_string(AIScore));
        ScorePlayer.setString(std::to_string(PlayerScore));

        window.clear();

        window.draw(LeftPaddle);
        window.draw(RightPaddle);
        window.draw(BorderRect);

        if (BallCountdown <= 0) {
            window.draw(Ball);
            window.draw(ScoreAI);
            window.draw(ScorePlayer);
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
            countdown.setScale(sf::Vector2f(1.f, 1.f));
            countdown.setLetterSpacing(1);
        }

        window.display();
    }
}