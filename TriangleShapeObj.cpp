#include "TriangleShapeObj.h"

TriangleShapeObj::TriangleShapeObj(float x, float y)
{
    float scale = 1.5f;
    posY = y;
    centerX = x;
    centerY = y;
    float base = 260.f * scale;
    float thickness = 20.f * scale;
    float angle = 60.f;
    float sideLength = base + 5.f * scale;
    float baseY = y + 80.f * scale;
    halfHeight = 150.f * scale;

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
    // Shift to the triangle's local coordinate frame (center is at 0,0 after rotatePointBack)
    float lx = local.x - centerX;   // if rotatePointBack already subtracts center, remove this
    float ly = local.y - centerY;

    // --- Bottom bar ---
    bool touchBottom =
        ly + ballRadius >= BASE_Y_LOC - THICKNESS / 2.f &&
        ly - ballRadius <= BASE_Y_LOC + THICKNESS / 2.f &&
        lx >= -HALF_BASE - ballRadius && lx <= HALF_BASE + ballRadius;

    // --- Left side: runs from (-HALF_BASE, BASE_Y_LOC) up to (0, APEX_Y_LOC) ---
    // At a given ly, the center-line X of the left bar:
    float t = (ly - BASE_Y_LOC) / (APEX_Y_LOC - BASE_Y_LOC); // 0 at base, 1 at apex
    float leftCenterX = -HALF_BASE + t * HALF_BASE;          // ?195 ? 0
    float rightCenterX = HALF_BASE - t * HALF_BASE;          //  195 ? 0

    bool touchLeft =
        ly >= APEX_Y_LOC - ballRadius && ly <= BASE_Y_LOC + ballRadius &&
        std::abs(lx - leftCenterX) <= THICKNESS / 2.f + ballRadius;

    bool touchRight =
        ly >= APEX_Y_LOC - ballRadius && ly <= BASE_Y_LOC + ballRadius &&
        std::abs(lx - rightCenterX) <= THICKNESS / 2.f + ballRadius;

    return touchBottom || touchLeft || touchRight;
}

sf::Color TriangleShapeObj::getCurrentTouchColor(sf::Vector2f ballPos) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);
    float lx = local.x - centerX;
    float ly = local.y - centerY;

    if (ly >= BASE_Y_LOC - THICKNESS)
        return bottomColor;

    float t = (ly - BASE_Y_LOC) / (APEX_Y_LOC - BASE_Y_LOC);
    float leftCenterX = -HALF_BASE + t * HALF_BASE;
    float rightCenterX = HALF_BASE - t * HALF_BASE;

    if (std::abs(lx - leftCenterX) < std::abs(lx - rightCenterX))
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