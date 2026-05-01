#pragma once
#include "Shape.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

class HorizontalLine : public Shape
{
private:
    sf::RectangleShape parts[4];

public:
    HorizontalLine(float y, float width);
    void draw(sf::RenderWindow& window) override;
};