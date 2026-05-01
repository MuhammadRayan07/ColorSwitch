#pragma once
#include "Shape.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

class CircleShapeObj : public Shape
{
private:
    static const int SEGMENTS = 40;
    sf::RectangleShape parts[4][SEGMENTS];

public:
    CircleShapeObj(float x, float y);
    void draw(sf::RenderWindow& window) override;
};