#include "PlusShape.h"

PlusShape::PlusShape(float x, float y, float size)
{
    float thickness = 20.f;
    float half = size / 2.f;

    sf::Color colors[4];
    getShuffledColors(colors);

    left.setSize({ half, thickness });
    left.setOrigin({ half, thickness / 2.f });
    left.setPosition({ x, y });
    left.setFillColor(colors[0]);

    right.setSize({ half, thickness });
    right.setOrigin({ 0.f, thickness / 2.f });
    right.setPosition({ x, y });
    right.setFillColor(colors[1]);

    top.setSize({ thickness, half });
    top.setOrigin({ thickness / 2.f, half });
    top.setPosition({ x, y });
    top.setFillColor(colors[2]);

    bottom.setSize({ thickness, half });
    bottom.setOrigin({ thickness / 2.f, 0.f });
    bottom.setPosition({ x, y });
    bottom.setFillColor(colors[3]);
}

void PlusShape::draw(sf::RenderWindow& window)
{
    window.draw(top);
    window.draw(bottom);
    window.draw(left);
    window.draw(right);
}