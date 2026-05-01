#include "PlusShape.h"

PlusShape::PlusShape(float x, float y, float size, float direction)
{
    posY = y;
    halfHeight = 90.f;
    centerX = x;
    centerY = y;
    rotationDirection = direction;

    float thickness = 20.f;
    float half = size / 2.f;

    sf::Color colors[4];
    getShuffledColors(colors);
    leftColor = colors[0];
    rightColor = colors[1];
    topColor = colors[2];
    bottomColor = colors[3];

    left.setSize({ half, thickness });
    left.setOrigin({ half, thickness / 2.f });
    left.setPosition({ x, y });
    left.setFillColor(leftColor);

    right.setSize({ half, thickness });
    right.setOrigin({ 0.f, thickness / 2.f });
    right.setPosition({ x, y });
    right.setFillColor(rightColor);

    top.setSize({ thickness, half });
    top.setOrigin({ thickness / 2.f, half });
    top.setPosition({ x, y });
    top.setFillColor(topColor);

    bottom.setSize({ thickness, half });
    bottom.setOrigin({ thickness / 2.f, 0.f });
    bottom.setPosition({ x, y });
    bottom.setFillColor(bottomColor);
}

bool PlusShape::isBallTouching(sf::Vector2f ballPos, float ballRadius) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);

    float armLength = 90.f;
    float thick = 20.f;

    bool horizontal =
        local.x + ballRadius >= -armLength &&
        local.x - ballRadius <= armLength &&
        local.y + ballRadius >= -thick / 2.f &&
        local.y - ballRadius <= thick / 2.f;

    bool vertical =
        local.x + ballRadius >= -thick / 2.f &&
        local.x - ballRadius <= thick / 2.f &&
        local.y + ballRadius >= -armLength &&
        local.y - ballRadius <= armLength;

    return horizontal || vertical;
}

sf::Color PlusShape::getCurrentTouchColor(sf::Vector2f ballPos) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);

    if (std::abs(local.x) > std::abs(local.y))
        return local.x < 0 ? leftColor : rightColor;
    else
        return local.y < 0 ? topColor : bottomColor;
}

void PlusShape::rotateShape(float angle)
{
    currentRotation += angle * rotationDirection;
}

void PlusShape::draw(sf::RenderWindow& window)
{
    sf::RenderStates states;
    states.transform.translate({ centerX, centerY });
    states.transform.rotate(sf::degrees(currentRotation));
    states.transform.translate({ -centerX, -centerY });

    window.draw(top, states);
    window.draw(bottom, states);
    window.draw(left, states);
    window.draw(right, states);
}