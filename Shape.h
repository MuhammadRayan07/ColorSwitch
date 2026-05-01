#pragma once
#include <SFML/Graphics.hpp>

class Shape
{
protected:
    float posY = 0.f;
    float halfHeight = 0.f;
    bool passed = false;
    bool collected = false;

public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void rotateShape(float angle) {}

    virtual bool isObstacle() const { return true; }

    virtual bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const
    {
        float topEdge = posY - halfHeight;
        float bottomEdge = posY + halfHeight;
        return ballPos.y + ballRadius > topEdge &&
            ballPos.y - ballRadius < bottomEdge;
    }

    bool isCollected() const { return collected; }
    void markCollected() { collected = true; }

    virtual float getX() const { return 0.f; }

    virtual sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const
    {
        return sf::Color::White;
    }

    virtual sf::Color getRandomAllowedColor() const
    {
        sf::Color colors[4] = {
            sf::Color(50,  226, 241),
            sf::Color(255, 232, 15),
            sf::Color(140, 18,  251),
            sf::Color(255, 0,   128)
        };
        return colors[rand() % 4];
    }

    virtual float getY()          const { return posY; }
    float getHalfHeight() const { return halfHeight; }
    bool  isPassed()      const { return passed; }
    void  markPassed() { passed = true; }

    virtual ~Shape() {}
};