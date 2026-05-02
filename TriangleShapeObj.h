#pragma once
#include "Shape.h"
#include "Globals.h"
#include "MathUtils.h"
#include <SFML/Graphics.hpp>
class TriangleShapeObj : public Shape
{
private:
    sf::RectangleShape left, right, bottom;
    sf::Color leftColor, rightColor, bottomColor;
    float centerX, centerY;
    float currentRotation = 0.f;
    float shapeScale = 1.0f;

public:
    TriangleShapeObj(float x, float y,float scale);
    void draw(sf::RenderWindow& window) override;
    void rotateShape(float angle) override;
    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override;
    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override;
    sf::Color getRandomAllowedColor() const override;
};