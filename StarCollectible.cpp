#include "StarCollectible.h"
#include <iostream>

StarCollectible::StarCollectible(float x, float y)
{
    if (!texture.loadFromFile("ColorSwitchSprites/Star.png"))
        std::cout << "Star NOT loaded\n";

    sprite = new sf::Sprite(texture);

    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    sprite->setScale({ 0.3f, 0.3f });
    sprite->setPosition({ x, y });
}

StarCollectible::~StarCollectible()
{
    delete sprite;
}

void StarCollectible::draw(sf::RenderWindow& window)
{
    window.draw(*sprite);
}