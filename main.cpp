#include <SFML/Graphics.hpp>
#include "Menus.h"

int main()
{ 
    sf::RenderWindow window(
        sf::VideoMode({ 800, 900 }),
        "Color Switch"
    );
    window.setFramerateLimit(60);
    srand(static_cast<unsigned int>(time(0)));
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

        float dt = dtClock.restart().asSeconds();
        float t = timeClock.getElapsedTime().asSeconds();

        menu.update(dt, t);

        window.clear(sf::Color(41, 41, 41));
        menu.draw(window);
        window.display();
    }
}