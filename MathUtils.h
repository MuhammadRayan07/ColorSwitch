#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

inline sf::Vector2f rotatePointBack(sf::Vector2f point,
    float centerX, float centerY,
    float rotation)
{
    float rad = -rotation * 3.14159265f / 180.f;
    float dx = point.x - centerX;
    float dy = point.y - centerY;
    float localX = dx * std::cos(rad) - dy * std::sin(rad);
    float localY = dx * std::sin(rad) + dy * std::cos(rad);
    return { localX, localY };
}