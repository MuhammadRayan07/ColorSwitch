#include "CircleShapeObj.h"
#include <cmath>

CircleShapeObj::CircleShapeObj(float x, float y)
{
    posY = y;
    centerX = x;
    centerY = y;
    halfHeight = 170.f;

    float radius = 150.f;
    float thickness = 20.f;

    sf::Color colors[4];
    getShuffledColors(colors);

    for (int i = 0; i < 4; i++)
        sectionColors[i] = colors[i];

    for (int p = 0; p < 4; p++)
    {
        for (int i = 0; i < SEGMENTS; i++)
        {
            float angle = (p * 90.f) + (i * (90.f / SEGMENTS));
            float rad = angle * 3.14159265f / 180.f;
            float px = x + cos(rad) * radius;
            float py = y + sin(rad) * radius;

            parts[p][i].setSize({ 12.f, thickness });
            parts[p][i].setOrigin({ 6.f, thickness / 2.f });
            parts[p][i].setPosition({ px, py });
            parts[p][i].setRotation(sf::degrees(angle + 90.f));
            parts[p][i].setFillColor(sectionColors[p]);
        }
    }
}

bool CircleShapeObj::isBallTouching(sf::Vector2f ballPos, float ballRadius) const
{
    float dx = ballPos.x - centerX;
    float dy = ballPos.y - centerY;
    float distance = std::sqrt(dx * dx + dy * dy);

    float outerRadius = 160.f;
    float innerRadius = 135.f;

    return distance + ballRadius >= innerRadius &&
        distance - ballRadius <= outerRadius;
}

sf::Color CircleShapeObj::getCurrentTouchColor(sf::Vector2f ballPos) const
{
    sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);

    float angle = atan2(local.y, local.x) * 180.f / 3.14159265f;
    if (angle < 0) angle += 360.f;

    int section = static_cast<int>(angle / 90.f);
    return sectionColors[section];
}

void CircleShapeObj::rotateShape(float angle)
{
    currentRotation += angle;
}

void CircleShapeObj::draw(sf::RenderWindow& window)
{
    sf::RenderStates states;
    states.transform.translate({ centerX, centerY });
    states.transform.rotate(sf::degrees(currentRotation));
    states.transform.translate({ -centerX, -centerY });

    for (int p = 0; p < 4; p++)
        for (int i = 0; i < SEGMENTS; i++)
            window.draw(parts[p][i], states);
}