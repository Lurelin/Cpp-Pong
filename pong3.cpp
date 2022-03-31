#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

float Screenwidth = 1920.f;
float Screenheight = 1080.f;
sf::RenderWindow window(sf::VideoMode(Screenwidth, Screenheight), "Pong! :)");
sf::View Mainview(sf::FloatRect(0, 0, 1920, 1080));

//Declaring Objects
sf::RectangleShape Ball;
sf::RectangleShape RightPaddle;
sf::RectangleShape LeftPaddle;
sf::RectangleShape DebugRect;


int main() {
    while (window.isOpen())
    {
        float ScreenRatio = Screenwidth / Screenheight;
        Mainview.setViewport(sf::FloatRect((1.f - (window.getSize().y * ScreenRatio) / (window.getSize().x * 1.f)) / 2, (1.f - (window.getSize().x * 1.f) / (window.getSize().y * ScreenRatio)) / 2, (window.getSize().y * ScreenRatio) / (window.getSize().x * 1.f), (window.getSize().x * 1.f) / (window.getSize().y * ScreenRatio)));
        if (Mainview.getViewport().top * 2 > Mainview.getViewport().left * 2) {
            Mainview.setSize(sf::Vector2f(Screenwidth / (1 - Mainview.getViewport().top * 2), Screenheight));
        } else {
            Mainview.setSize(sf::Vector2f(Screenwidth, Screenheight / (1 - Mainview.getViewport().left * 2)));   
        }
        window.setView(Mainview);

        Ball.setSize(sf::Vector2f(40, 40));
        Ball.setOrigin(sf::Vector2f(20, 20));
        Ball.setPosition(960, 540);
        Ball.setFillColor(sf::Color::Red);

        RightPaddle.setSize(sf::Vector2f(30, 200));
        RightPaddle.setOrigin(sf::Vector2f(15, 100));
        RightPaddle.setPosition(60, 540);
        RightPaddle.setFillColor(sf::Color::Red);

        DebugRect.setSize(sf::Vector2f(1920, 1080));
        DebugRect.setOrigin(sf::Vector2f(960, 540));
        DebugRect.setPosition(960, 540);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(DebugRect);
        window.draw(Ball);
        window.draw(LeftPaddle);
        window.draw(RightPaddle);

        window.display();
    }
}