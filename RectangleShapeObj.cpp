#include "RectangleShapeObj.h"

RectangleShapeObj::RectangleShapeObj(float x, float y)
{
    float size = 250.f;
    float thick = 20.f;

    top.setSize({ size, thick });
    bottom.setSize({ size, thick });
    left.setSize({ thick, size });
    right.setSize({ thick, size });

    top.setOrigin({ size / 2.f, thick / 2.f });
    bottom.setOrigin({ size / 2.f, thick / 2.f });
    left.setOrigin({ thick / 2.f, size / 2.f });
    right.setOrigin({ thick / 2.f, size / 2.f });

    top.setPosition({ x, y - size / 2.f });
    bottom.setPosition({ x, y + size / 2.f });
    left.setPosition({ x - size / 2.f + thick / 2.f, y });
    right.setPosition({ x + size / 2.f - thick / 2.f, y });

    sf::Color colors[4];
    getShuffledColors(colors);

    top.setFillColor(colors[0]);
    bottom.setFillColor(colors[1]);
    left.setFillColor(colors[2]);
    right.setFillColor(colors[3]);
}

void RectangleShapeObj::draw(sf::RenderWindow& window)
{
    window.draw(left);
    window.draw(right);
    window.draw(top);
    window.draw(bottom);
}