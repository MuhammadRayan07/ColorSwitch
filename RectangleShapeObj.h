#pragma once
#include "Shape.h"
#include "Globals.h"
#include "MathUtils.h"
#include <SFML/Graphics.hpp>
class RectangleShapeObj : public Shape
{
private:
    sf::RectangleShape top, bottom, left, right;
    sf::Color colorTop, colorBottom, colorLeft, colorRight;
    float centerX, centerY;
    float currentRotation = 0.f;

public:
    RectangleShapeObj(float x, float y);
    void draw(sf::RenderWindow& window) override;
    void rotateShape(float angle) override;
    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override;
    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override;
};