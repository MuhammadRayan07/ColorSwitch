#pragma once
#include "Shape.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

class TriangleShapeObj : public Shape
{
private:
    sf::RectangleShape left, right, bottom;

public:
    TriangleShapeObj(float x, float y);
    void draw(sf::RenderWindow& window) override;
};