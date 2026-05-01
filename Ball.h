
#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
private:
    sf::CircleShape circle;
    float velocityY;

public:
    Ball(float radius, float startX, float startY);

    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void move(float dx, float dy);

    void setVelocityY(float v);
    float getVelocityY() const;
    void addVelocityY(float value);
    void setRandomColor();
    float getRadius() const;
    sf::Color getColor() const;
    void setColor(sf::Color newColor);
};