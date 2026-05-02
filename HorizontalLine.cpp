#include "HorizontalLine.h"

HorizontalLine::HorizontalLine(float y, float width)
{
    posY = y;
    this->width = width;
    this->y = y;
    halfHeight = 20.f;

    float segmentWidth = width / 4.f;

    sf::Color colors[4];
    getShuffledColors(colors);

    for (int i = 0; i < 4; i++)
        segmentColors[i] = colors[i];

    for (int copy = 0; copy < 2; copy++)
    {
        for (int i = 0; i < 4; i++)
        {
            int index = copy * 4 + i;
            parts[index].setSize({ segmentWidth, 20.f });
            parts[index].setOrigin({ segmentWidth / 2.f, 10.f });
            parts[index].setFillColor(segmentColors[i]);
        }
    }
}

bool HorizontalLine::isBallTouching(sf::Vector2f ballPos, float ballRadius) const
{
    return ballPos.y + ballRadius >= y - 10.f &&
        ballPos.y - ballRadius <= y + 10.f;
}

sf::Color HorizontalLine::getCurrentTouchColor(sf::Vector2f ballPos) const
{
    float segmentWidth = width / 4.f;
    float adjustedX = ballPos.x - offset;

    while (adjustedX < 0)     adjustedX += width;
    while (adjustedX >= width) adjustedX -= width;

    int section = static_cast<int>(adjustedX / segmentWidth);
    return segmentColors[section];
}

void HorizontalLine::rotateShape(float angle)
{
    offset += speed;
    if (offset >= width) offset = 0.f;

    float segmentWidth = width / 4.f;

    for (int copy = 0; copy < 2; copy++)
    {
        float copyOffset = offset - copy * width;
        for (int i = 0; i < 4; i++)
        {
            int index = copy * 4 + i;
            float x = segmentWidth / 2.f + i * segmentWidth + copyOffset;
            parts[index].setPosition({ x, y });
        }
    }
}

void HorizontalLine::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < 8; i++)
        window.draw(parts[i]);
}