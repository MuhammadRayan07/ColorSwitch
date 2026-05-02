#include "Ball.h"
#include"Globals.h"
Ball::Ball(float radius, float startX, float startY)
{
    circle.setRadius(radius);
    circle.setFillColor(sf::Color(128, 213, 111));
    circle.setOrigin({ radius, radius });
    circle.setPosition({ startX, startY });
    circle.setFillColor(palette[rand() % 4]);
    velocityY = 0.f;
}

void Ball::draw(sf::RenderWindow& window) { window.draw(circle); }

void Ball::setPosition(float x, float y) { circle.setPosition({ x, y }); }

sf::Vector2f Ball::getPosition() const { return circle.getPosition(); }

void Ball::move(float dx, float dy) { circle.move({ dx, dy }); }

void Ball::setVelocityY(float v) { velocityY = v; }

float Ball::getVelocityY() const { return velocityY; }

void Ball::addVelocityY(float value) { velocityY += value; }
void Ball::setRandomColor()
{
    circle.setFillColor(palette[rand() % 4]);
}

float Ball::getRadius() const
{
    return circle.getRadius();
}

sf::Color Ball::getColor() const
{
    return circle.getFillColor();
}

void Ball::setColor(sf::Color newColor)
{
    circle.setFillColor(newColor);
}