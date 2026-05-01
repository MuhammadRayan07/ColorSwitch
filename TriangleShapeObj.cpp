#include "TriangleShapeObj.h"

TriangleShapeObj::TriangleShapeObj(float x, float y)
{
    float base = 260.f;
    float thickness = 20.f;
    float angle = 60.f;

    float sideLength = base + 5.f;

    sf::Color colors[4];
    getShuffledColors(colors);

    float baseY = y + 80.f;

    bottom.setSize({ base, thickness });
    bottom.setOrigin({ base / 2.f, thickness / 2.f });
    bottom.setPosition({ x, baseY });
    bottom.setFillColor(colors[0]);

    left.setSize({ sideLength, thickness });
    left.setOrigin({ 0.f, thickness / 2.f });
    left.setPosition({ x - base / 2.f, baseY });
    left.setRotation(sf::degrees(-angle));
    left.setFillColor(colors[1]);

    right.setSize({ sideLength, thickness });
    right.setOrigin({ sideLength, thickness / 2.f });
    right.setPosition({ x + base / 2.f, baseY });
    right.setRotation(sf::degrees(angle));
    right.setFillColor(colors[2]);
}

void TriangleShapeObj::draw(sf::RenderWindow& window)
{
    window.draw(left);
    window.draw(right);
    window.draw(bottom);
}