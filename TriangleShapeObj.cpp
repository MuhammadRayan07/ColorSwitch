#include "TriangleShapeObj.h"

TriangleShapeObj::TriangleShapeObj(float x, float y,float scale)
{

    posY = y;
    centerX = x;
    centerY = y;
    float base = 260.f * scale;
    float thickness = 20.f * scale;
    float angle = 60.f;
    float sideLength = base + 5.f * scale;
    float baseY = y + 80.f * scale;
    halfHeight = 150.f * scale;
    shapeScale = scale;

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

// Replace the static constexpr block with these:
static const float SCALE = 1.5f;
static const float HALF_BASE = 130.f * 1.5f;          // 195.0
static const float THICKNESS = 20.f * 1.5f;          // 30.0
static const float BASE_Y_LOC = 80.f * 1.5f;          // 120.0
static const float SIDE_LEN = 265.f * 1.5f;          // 397.5
// sin(60°) = 0.86602540378f  — pre-computed, no runtime call needed
static const float APEX_Y_LOC = BASE_Y_LOC - SIDE_LEN * 0.86602540378f; // ? ?224.3

bool TriangleShapeObj::isBallTouching(sf::Vector2f ballPos, float ballRadius) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);

    float baseY = 80.f * shapeScale;
    float thickness = 20.f * shapeScale;
    float halfBase = 130.f * shapeScale;
    float apexY = baseY - (265.f * shapeScale) * 0.86602540378f;

    bool touchBottom =
        local.y + ballRadius >= baseY - thickness / 2.f &&
        local.y - ballRadius <= baseY + thickness / 2.f &&
        local.x >= -halfBase - ballRadius && local.x <= halfBase + ballRadius;

    float t = (local.y - baseY) / (apexY - baseY);
    t = std::max(0.f, std::min(1.f, t));
    float leftCenterX = -halfBase + t * halfBase;
    float rightCenterX = halfBase - t * halfBase;

    bool touchLeft =
        local.y >= apexY - ballRadius && local.y <= baseY + ballRadius &&
        std::abs(local.x - leftCenterX) <= thickness / 2.f + ballRadius;

    bool touchRight =
        local.y >= apexY - ballRadius && local.y <= baseY + ballRadius &&
        std::abs(local.x - rightCenterX) <= thickness / 2.f + ballRadius;

    return touchBottom || touchLeft || touchRight;
}

sf::Color TriangleShapeObj::getCurrentTouchColor(sf::Vector2f ballPos) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);

    float baseY = 80.f * shapeScale;
    float thickness = 20.f * shapeScale;
    float halfBase = 130.f * shapeScale;
    float apexY = baseY - (265.f * shapeScale) * 0.86602540378f;

    if (local.y >= baseY - thickness)
        return bottomColor;

    float t = (local.y - baseY) / (apexY - baseY);
    t = std::max(0.f, std::min(1.f, t));
    float leftCenterX = -halfBase + t * halfBase;
    float rightCenterX = halfBase - t * halfBase;

    if (std::abs(local.x - leftCenterX) < std::abs(local.x - rightCenterX))
        return leftColor;
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
sf::Color TriangleShapeObj::getRandomAllowedColor() const
{
    int r = rand() % 3;
    if (r == 0) return bottomColor;
    if (r == 1) return leftColor;
    return rightColor;
}