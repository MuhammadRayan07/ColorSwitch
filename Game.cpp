#include "Game.h"

// ---- palette and getShuffledColors ----
sf::Color palette[4] = {
    sf::Color(50,  226, 241),
    sf::Color(255, 232, 15),
    sf::Color(140, 18,  251),
    sf::Color(255, 0,   128)
};

void getShuffledColors(sf::Color colors[4])
{
    for (int i = 0; i < 4; i++)
        colors[i] = palette[i];

    for (int i = 3; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(colors[i], colors[j]);
    }
}

// ---- Free functions ----
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
    float x, float y, float width)
{
    int type = rand() % 5;

    if (type == 0)
        addShape(shapes, count, capacity, new CircleShapeObj(x, y));
    else if (type == 1)
        addShape(shapes, count, capacity, new RectangleShapeObj(x, y));
    else if (type == 2)
        addShape(shapes, count, capacity, new TriangleShapeObj(x, y));
    else if (type == 3)
        addShape(shapes, count, capacity, new HorizontalLine(y, width));
    else
    {
        float gapX = 170.f;
        addShape(shapes, count, capacity, new PlusShape(x - gapX / 2.f, y, 130.f));
        addShape(shapes, count, capacity, new PlusShape(x + gapX / 2.f, y, 150.f));
    }

    addShape(shapes, count, capacity, new StarCollectible(x, y));
}

void removeFirst(Shape**& shapes, int& count)
{
    delete shapes[0];
    for (int i = 1; i < count; i++)
        shapes[i - 1] = shapes[i];
    count--;
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