#pragma once
#include "Shape.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

class RectangleShapeObj : public Shape
{
private:
    sf::RectangleShape top, bottom, left, right;

public:
    RectangleShapeObj(float x, float y);
    void draw(sf::RenderWindow& window) override;
};