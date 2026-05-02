#include "RectangleShapeObj.h"

RectangleShapeObj::RectangleShapeObj(float x, float y, float scale)
{
    shapeScale = scale;
    posY = y;
    centerX = x;
    centerY = y;
    halfHeight = 140.f * scale;

    float size = 250.f * scale;
    float thick = 20.f * scale;

    top.setSize({ size,  thick });
    bottom.setSize({ size,  thick });
    left.setSize({ thick, size });
    right.setSize({ thick, size });

    top.setOrigin({ size / 2.f,  thick / 2.f });
    bottom.setOrigin({ size / 2.f,  thick / 2.f });
    left.setOrigin({ thick / 2.f, size / 2.f });
    right.setOrigin({ thick / 2.f, size / 2.f });

    top.setPosition({ x, y - size / 2.f });
    bottom.setPosition({ x, y + size / 2.f });
    left.setPosition({ x - size / 2.f + thick / 2.f, y });
    right.setPosition({ x + size / 2.f - thick / 2.f, y });

    sf::Color colors[4];
    getShuffledColors(colors);
    colorTop = colors[0];
    colorBottom = colors[1];
    colorLeft = colors[2];
    colorRight = colors[3];

    top.setFillColor(colorTop);
    bottom.setFillColor(colorBottom);
    left.setFillColor(colorLeft);
    right.setFillColor(colorRight);
}

bool RectangleShapeObj::isBallTouching(sf::Vector2f ballPos, float ballRadius) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);

    float halfSize = 125.f * shapeScale;
    float thick = 20.f * shapeScale;

    bool touchTop =
        local.y + ballRadius >= -halfSize &&
        local.y - ballRadius <= -halfSize + thick &&
        local.x >= -halfSize && local.x <= halfSize;

    bool touchBottom =
        local.y + ballRadius >= halfSize - thick &&
        local.y - ballRadius <= halfSize &&
        local.x >= -halfSize && local.x <= halfSize;

    bool touchLeft =
        local.x + ballRadius >= -halfSize &&
        local.x - ballRadius <= -halfSize + thick &&
        local.y >= -halfSize && local.y <= halfSize;

    bool touchRight =
        local.x + ballRadius >= halfSize - thick &&
        local.x - ballRadius <= halfSize &&
        local.y >= -halfSize && local.y <= halfSize;

    return touchTop || touchBottom || touchLeft || touchRight;
}

sf::Color RectangleShapeObj::getCurrentTouchColor(sf::Vector2f ballPos) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);

    if (std::abs(local.x) > std::abs(local.y))
        return local.x < 0 ? colorLeft : colorRight;
    else
        return local.y < 0 ? colorTop : colorBottom;
}

void RectangleShapeObj::rotateShape(float angle)
{
    currentRotation += angle;
}

void RectangleShapeObj::draw(sf::RenderWindow& window)
{
    sf::RenderStates states;
    states.transform.translate({ centerX, centerY });
    states.transform.rotate(sf::degrees(currentRotation));
    states.transform.translate({ -centerX, -centerY });

    window.draw(left, states);
    window.draw(right, states);
    window.draw(top, states);
    window.draw(bottom, states);
}