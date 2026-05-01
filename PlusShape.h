#pragma once
#include "Shape.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

class PlusShape : public Shape
{
private:
    sf::RectangleShape left, right, top, bottom;

public:
    PlusShape(float x, float y, float size);
    void draw(sf::RenderWindow& window) override;
};