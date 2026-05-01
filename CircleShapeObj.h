#pragma once
#include "Shape.h"
#include "Globals.h"
#include "MathUtils.h"
#include <SFML/Graphics.hpp>
class CircleShapeObj : public Shape
{
private:
    static const int SEGMENTS = 40;
    sf::RectangleShape parts[4][SEGMENTS];
    sf::Color sectionColors[4];
    float centerX, centerY;
    float currentRotation = 0.f;

public:
    CircleShapeObj(float x, float y);
    void draw(sf::RenderWindow& window) override;
    void rotateShape(float angle) override;
    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override;
    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override;
};