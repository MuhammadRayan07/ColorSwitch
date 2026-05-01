#pragma once
#include "Shape.h"
#include "Ball.h"
#include "Camera.h"

void resizeArray(Shape**& shapes, int& capacity);
void addShape(Shape**& shapes, int& count, int& capacity, Shape* newShape);
void spawnShape(Shape**& shapes, int& count, int& capacity, float x, float y, float width);
void removeFirst(Shape**& shapes, int& count);

void applyGravity(Ball& ball, float gravity);
void moveBall(Ball& ball);
void resetBallOnGround(Ball& ball, float groundY);
void updateCamera(Camera& camera, Ball& ball, int width, int height);