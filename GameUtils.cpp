#include "GameUtils.h"
#include "CircleShapeObj.h"
#include "RectangleShapeObj.h"
#include "TriangleShapeObj.h"
#include "HorizontalLine.h"
#include "PlusShape.h"
#include "StarCollectible.h"
#include"difficulty.h"

#include <cstdlib>


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
    else                                 scale = 1.0f;

    int type = rand() % 5;

    if (type == 0)
        addShape(shapes, count, capacity, new CircleShapeObj(x, y, scale));
    else if (type == 1)
        addShape(shapes, count, capacity, new RectangleShapeObj(x, y, scale));
    else if (type == 2)
        addShape(shapes, count, capacity, new TriangleShapeObj(x, y, scale));
    else if (type == 3)
        addShape(shapes, count, capacity, new HorizontalLine(y, width, scale));
    else
    {
        if (diff == Difficulty::Hard)
        {
            float gapX = 170.f;
            addShape(shapes, count, capacity, new PlusShape(x - gapX / 2.f, y, 150.f * scale, -1.0f, scale));
            addShape(shapes, count, capacity, new PlusShape(x + gapX / 2.f, y, 150.f * scale, 1.0f, scale));
        }
        else
        {
            
            float shift = 50.f + static_cast<float>(rand() % 41); 
            shift = -shift;

            addShape(shapes, count, capacity, new PlusShape(x + shift, y, 150.f * scale, -1.0f, scale));
        }
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