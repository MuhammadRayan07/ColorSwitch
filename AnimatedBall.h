#pragma once
#include <SFML/Graphics.hpp>

class AnimatedBall
{
private:
    sf::CircleShape ball;
    float y;
    float x;
    float velocity;

    const float g = 800.f;
    const float topLimit = 30.f;
    const float bottomLimit = 540.f;

public:
    AnimatedBall();

    AnimatedBall(float xPos, sf::Color color);

    void update(float dt);
    void draw(sf::RenderWindow& window);
};