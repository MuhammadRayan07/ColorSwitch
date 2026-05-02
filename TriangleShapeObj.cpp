#include "TriangleShapeObj.h"

TriangleShapeObj::TriangleShapeObj(float x, float y)
{
    posY = y;
    centerX = x;
    centerY = y;
    halfHeight = 150.f;

    float base = 260.f;
    float thickness = 20.f;
    float angle = 60.f;
    float sideLength = base + 5.f;
    float baseY = y + 80.f;

    sf::Color colors[4];
    getShuffledColors(colors);
    bottomColor = colors[0];
    leftColor = colors[1];
    rightColor = colors[2];

    bottom.setSize({ base, thickness });
    bottom.setOrigin({ base / 2.f, thickness / 2.f });
    bottom.setPosition({ x, baseY });
    bottom.setFillColor(bottomColor);

    left.setSize({ sideLength, thickness });
    left.setOrigin({ 0.f, thickness / 2.f });
    left.setPosition({ x - base / 2.f, baseY });
    left.setRotation(sf::degrees(-angle));
    left.setFillColor(leftColor);

    right.setSize({ sideLength, thickness });
    right.setOrigin({ sideLength, thickness / 2.f });
    right.setPosition({ x + base / 2.f, baseY });
    right.setRotation(sf::degrees(angle));
    right.setFillColor(rightColor);
}

bool TriangleShapeObj::isBallTouching(sf::Vector2f ballPos, float ballRadius) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);

    float baseY = 80.f;
    float thickness = 20.f;
    float halfBase = 130.f;

    bool touchBottom =
        local.y + ballRadius >= baseY - thickness / 2.f &&
        local.y - ballRadius <= baseY + thickness / 2.f &&
        local.x >= -halfBase && local.x <= halfBase;

    float leftSideX = -halfBase + ((local.y + 130.f) / 210.f) * halfBase;
    float rightSideX = halfBase - ((local.y + 130.f) / 210.f) * halfBase;

    bool touchLeft =
        local.y >= -130.f && local.y <= baseY &&
        std::abs(local.x - leftSideX) <= thickness + ballRadius;

    bool touchRight =
        local.y >= -130.f && local.y <= baseY &&
        std::abs(local.x - rightSideX) <= thickness + ballRadius;

    return touchBottom || touchLeft || touchRight;
}

sf::Color TriangleShapeObj::getCurrentTouchColor(sf::Vector2f ballPos) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);

    float baseY = 80.f;
    float thickness = 20.f;
    float halfBase = 130.f;

    if (local.y >= baseY - thickness * 2.f)
        return bottomColor;

    float leftSideX = -halfBase + ((local.y + 130.f) / 210.f) * halfBase;
    float rightSideX = halfBase - ((local.y + 130.f) / 210.f) * halfBase;

    if (std::abs(local.x - leftSideX) < std::abs(local.x - rightSideX))
        return leftColor;

    return rightColor;
}

sf::Color TriangleShapeObj::getRandomAllowedColor() const
{
    int r = rand() % 3;
    if (r == 0) return bottomColor;
    if (r == 1) return leftColor;
    return rightColor;
}

void TriangleShapeObj::rotateShape(float angle)
{
    currentRotation += angle;
}

void TriangleShapeObj::draw(sf::RenderWindow& window)
{
    sf::RenderStates states;
    states.transform.translate({ centerX, centerY });
    states.transform.rotate(sf::degrees(currentRotation));
    states.transform.translate({ -centerX, -centerY });

    window.draw(left, states);
    window.draw(right, states);
    window.draw(bottom, states);
}