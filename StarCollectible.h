#pragma once
#include "Shape.h"
#include <SFML/Graphics.hpp>

class StarCollectible : public Shape
{
private:
    sf::Texture  texture;
    sf::Sprite* sprite;
    float        centerX;
    float        centerY;

public:
    StarCollectible(float x, float y);
    ~StarCollectible();

    bool  isObstacle()  const override { return false; }
    float getX()        const override { return centerX; }
    float getY()        const override{ return centerY; }

    void draw(sf::RenderWindow& window) override;
};