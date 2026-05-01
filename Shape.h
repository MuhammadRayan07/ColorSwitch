#pragma once
#include <SFML/Graphics.hpp>

class Shape
{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Shape() {}
};