#pragma once
#include "Shape.h"
#include "Globals.h"
#include "MathUtils.h"
#include <SFML/Graphics.hpp>
class PlusShape : public Shape
{
private:
    sf::RectangleShape left, right, top, bottom;
    sf::Color leftColor, rightColor, topColor, bottomColor;
    float centerX, centerY;
    float currentRotation = 0.f;
    float rotationDirection;

public:
    PlusShape(float x, float y, float size, float direction);
    void draw(sf::RenderWindow& window) override;
    void rotateShape(float angle) override;
    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override;
    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override;
};