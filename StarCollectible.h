#pragma once
#include "Shape.h"
#include <SFML/Graphics.hpp>

class StarCollectible : public Shape
{
private:
    sf::Texture texture;
    sf::Sprite* sprite;

public:
    StarCollectible(float x, float y);
    ~StarCollectible();

    void draw(sf::RenderWindow& window) override;
};