#include "HorizontalLine.h"

HorizontalLine::HorizontalLine(float y, float width)
{
    float segmentWidth = width / 4.f;

    sf::Color colors[4];
    getShuffledColors(colors);

    for (int i = 0; i < 4; i++)
    {
        parts[i].setSize({ segmentWidth, 20.f });
        parts[i].setFillColor(colors[i]);
        parts[i].setOrigin({ segmentWidth / 2.f, 10.f });
        parts[i].setPosition({
            segmentWidth / 2.f + i * segmentWidth,
            y
            });
    }
}

void HorizontalLine::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < 4; i++)
        window.draw(parts[i]);
}