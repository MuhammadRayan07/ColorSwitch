#pragma once
#include "Shape.h"
#include "Globals.h"
#include "MathUtils.h"
#include <SFML/Graphics.hpp>

class CircleShapeObj : public Shape
{
private:
    static const int div = 40;
    sf::RectangleShape parts[4][div];
    sf::Color sectionColors[4];
    float centerX, centerY;
    float currentRotation = 0.f;
    float shapeScale = 1.0f;

public:
    CircleShapeObj(float x, float y, float scale = 1.0f);
    void draw(sf::RenderWindow& window) override;
    void rotateShape(float angle) override;
    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override;
    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override;
};