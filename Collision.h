#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

class Ball;
class Shape;

bool sameColor(sf::Color a, sf::Color b);
void checkShapePassCollision(Ball& ball, Shape** shapes, int shapeCount);
bool checkWrongColorCollision(Ball& ball, Shape** shapes, int shapeCount);
bool sameColor(sf::Color a, sf::Color b);
bool checkStarCollection(Ball& ball, Shape** shapes, int shapeCount);

