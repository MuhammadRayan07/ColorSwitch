#include "CircleShapeObj.h"
#include <cmath>

CircleShapeObj::CircleShapeObj(float x, float y)
{
    float radius = 150.f;
    float thickness = 20.f;

    sf::Color colors[4];
    getShuffledColors(colors);

    for (int p = 0; p < 4; p++)
    {
        for (int i = 0; i < SEGMENTS; i++)
        {
            float angle = (p * 90.f) + (i * (90.f / SEGMENTS));
            float rad = angle * 3.14159265f / 180.f;

            float px = x + cos(rad) * radius;
            float py = y + sin(rad) * radius;

            parts[p][i].setSize({ 12.f, thickness });
            parts[p][i].setOrigin({ 6.f, thickness / 2.f });
            parts[p][i].setPosition({ px, py });
            parts[p][i].setRotation(sf::degrees(angle + 90.f));
            parts[p][i].setFillColor(colors[p]);
        }
    }
}

void CircleShapeObj::draw(sf::RenderWindow& window)
{
    for (int p = 0; p < 4; p++)
        for (int i = 0; i < SEGMENTS; i++)
            window.draw(parts[p][i]);
}