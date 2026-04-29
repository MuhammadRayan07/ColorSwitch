#pragma once
#include <SFML/Graphics.hpp>

class AnimatedBall
{
private:
    sf::CircleShape ball;
    float y;
    float x;
    float velocity;

    static constexpr float g = 800.f;
    static constexpr float topLimit = 30.f;
    static constexpr float bottomLimit = 540.f;

public:
    AnimatedBall();

    AnimatedBall(float xPos, sf::Color color);

    void update(float dt);
    void draw(sf::RenderWindow& window);
};