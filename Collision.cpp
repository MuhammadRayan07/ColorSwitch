#include "Shape.h"
#include "Ball.h"
#include "Collision.h"
#include <iostream>
#include <cmath>

bool sameColor(sf::Color a, sf::Color b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

void checkShapePassCollision(Ball& ball, Shape** shapes, int shapeCount)
{
    for (int i = 0; i < shapeCount; i++)
    {
        if (!shapes[i] || shapes[i]->isCollected() || !shapes[i]->isObstacle())
            continue;

        float ballY = ball.getPosition().y;
        float passLine = shapes[i]->getY()
            - shapes[i]->getHalfHeight()
            - ball.getRadius()
            - 15.f;

        if (!shapes[i]->isPassed() && ballY < passLine)
        {
            int next = i + 1;
            while (next < shapeCount &&
                (!shapes[next] || !shapes[next]->isObstacle()))
                next++;

            if (next < shapeCount)
                ball.setColor(shapes[next]->getRandomAllowedColor());
            else
                ball.setColor(shapes[i]->getRandomAllowedColor());

            shapes[i]->markPassed();
        }
    }
}

bool checkWrongColorCollision(Ball& ball, Shape** shapes, int shapeCount)
{
    for (int i = 0; i < shapeCount; i++)
    {
        if (!shapes[i] || shapes[i]->isCollected() || !shapes[i]->isObstacle())
            continue;

        if (shapes[i]->isBallTouching(ball.getPosition(), ball.getRadius()))
        {
            sf::Color touchColor =
                shapes[i]->getCurrentTouchColor(ball.getPosition());

            if (!sameColor(ball.getColor(), touchColor))
            {
                std::cout << "Wrong collision from shape index: " << i << "\n";
                return true;
            }
        }
    }
    return false;
}

bool checkStarCollection(Ball& ball, Shape** shapes, int shapeCount)
{
    for (int i = 0; i < shapeCount; i++)
    {
        if (!shapes[i] || shapes[i]->isObstacle() || shapes[i]->isCollected())
            continue;

        sf::Vector2f ballPos = ball.getPosition();
        float dx = ballPos.x - shapes[i]->getX();
        float dy = ballPos.y - shapes[i]->getY();
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < ball.getRadius() + 25.f)
        {
            shapes[i]->markCollected();
            return true;
        }
    }
    return false;
}