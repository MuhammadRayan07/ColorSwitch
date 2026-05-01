#pragma once
#include "Shape.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

class HorizontalLine : public Shape
{
private:
    sf::RectangleShape parts[8];
    sf::Color segmentColors[4];
    float offset = 0.f;
    float speed = 2.5f;
    float width;
    float y;

public:
    HorizontalLine(float y, float width);
    void draw(sf::RenderWindow& window) override;
    void rotateShape(float angle) override;
    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override;
    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override;
};