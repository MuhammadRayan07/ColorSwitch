#include <SFML/Graphics.hpp>
#include "Menus.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 800u, 900u }),
        "Color Switch"
    );
    window.setFramerateLimit(60);

    Menu menu;

    sf::Clock dtClock;
    sf::Clock timeClock;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            menu.handleEvent(*event);
        }

        if (menu.shouldClose())
            window.close();

        // ---- Update ----
        float dt = dtClock.restart().asSeconds();
        float t = timeClock.getElapsedTime().asSeconds();

        menu.update(dt, t);

        // ---- Draw ----
        window.clear(sf::Color(41, 41, 41));
        menu.draw(window);
        window.display();
    }
}