#include "AnimatedBall.h"
AnimatedBall::AnimatedBall()
    : x(0.f), y(0.f), velocity(0.f)
{
    ball.setRadius(18.f);
    ball.setOrigin({ 18.f, 18.f });
    ball.setFillColor(sf::Color::Transparent);
}

AnimatedBall::AnimatedBall(float xPos, sf::Color color)
    : x(xPos), y(450.f), velocity(-620.f)
{
    ball.setRadius(18.f);
    ball.setOrigin({ 18.f, 18.f });
    ball.setFillColor(color);
}

void AnimatedBall::update(float dt)
{
    velocity += g * dt;
    y += velocity * dt;

    if (y < topLimit)
    {
        y = topLimit;
        velocity *= -1.f;
    }

    if (y > bottomLimit)
    {
        y = bottomLimit;
        velocity = -620.f;
    }

    ball.setPosition({ x, y });
}

void AnimatedBall::draw(sf::RenderWindow& window)
{
    window.draw(ball);
}