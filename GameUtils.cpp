#include "GameUtils.h"
#include "CircleShapeObj.h"
#include "RectangleShapeObj.h"
#include "TriangleShapeObj.h"
#include "HorizontalLine.h"
#include "PlusShape.h"
#include "StarCollectible.h"
#include"difficulty.h"
#include"ShapeFactory.h"
#include <cstdlib>
#include<iostream>

void resizeArray(Shape**& shapes, int& capacity)
{
    int newCapacity = capacity * 2;
    Shape** newArr = new Shape * [newCapacity];

    for (int i = 0; i < capacity; i++)
        newArr[i] = shapes[i];

    delete[] shapes;
    shapes = newArr;
    capacity = newCapacity;
}

void addShape(Shape**& shapes, int& count, int& capacity, Shape* newShape)
{
    if (count >= capacity)
        resizeArray(shapes, capacity);

    shapes[count++] = newShape;
}

void spawnShape(Shape**& shapes, int& count, int& capacity,
    float x, float y, float width, Difficulty diff)
{
    float scale = 1.0f;
    if (diff == Difficulty::Easy)   scale = 1.5f;
    else if (diff == Difficulty::Medium) scale = 1.25f;

    int type = rand() % 5;

    try
    {
        if (type == 4) // plus shape special case
        {
            if (diff == Difficulty::Hard)
            {
                float gapX = 170.f;
                addShape(shapes, count, capacity,
                    new PlusShape(x - gapX / 2.f, y, 150.f * scale, -1.0f, scale));
                addShape(shapes, count, capacity,
                    new PlusShape(x + gapX / 2.f, y, 150.f * scale, 1.0f, scale));
            }
            else
            {
                addShape(shapes, count, capacity,
                    new PlusShape(x, y, 150.f * scale, 1.0f, scale));
            }
        }
        else
        {
            Shape* s = ShapeFactory::createRandom(type, x, y, width, scale, diff);
            addShape(shapes, count, capacity, s);
        }
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "Shape spawn error: " << e.what() << "\n";
        // fallback to circle if unknown type
        addShape(shapes, count, capacity,
            ShapeFactory::createShape<CircleShapeObj>(x, y, scale));
    }

    addShape(shapes, count, capacity, new StarCollectible(x, y));
}
void applyGravity(Ball& ball, float gravity)
{
    ball.addVelocityY(gravity);
}

void moveBall(Ball& ball)
{
    ball.move(0.f, ball.getVelocityY());
}

void resetBallOnGround(Ball& ball, float groundY)
{
    if (ball.getPosition().y >= groundY)
    {
        ball.setPosition(ball.getPosition().x, groundY);
        ball.setVelocityY(0.f);
    }
}

void updateCamera(Camera& camera, Ball& ball, int width, int height)
{
    float triggerLine = camera.getCenter().y;

    if (ball.getPosition().y < triggerLine)
    {
        float diff = ball.getPosition().y - triggerLine;
        camera.setCameraVelocity(diff * camera.getCameraFollowSpeed());
    }
    else
    {
        camera.setCameraVelocity(0.f);
    }

    camera.move(0.f, camera.getCameraVelocity());

    if (camera.getCenter().y > height / 2.f)
    {
        camera.setCenter(width / 2.f, height / 2.f);
        camera.setCameraVelocity(0.f);
    }
}
void removeFirst(Shape**& shapes, int& count)
{
    delete shapes[0];
    for (int i = 1; i < count; i++)
        shapes[i - 1] = shapes[i];
    count--;
}