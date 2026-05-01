#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

extern sf::Color palette[4];
void getShuffledColors(sf::Color colors[4]);

class Shape
{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Shape() {}
};

class CircleShapeObj : public Shape
{
private:
    static const int SEGMENTS = 40;
    sf::RectangleShape parts[4][SEGMENTS];

public:
    CircleShapeObj(float x, float y)
    {
        float radius = 150.f;
        float thickness = 20.f;
        sf::Color colors[4];
        getShuffledColors(colors);

        for (int p = 0; p < 4; p++)
        {
            for (int i = 0; i < SEGMENTS; i++)
            {
                float angle = (p * 90.f) + (i * (90.f / SEGMENTS));
                float rad = angle * 3.14159265f / 180.f;
                float px = x + cos(rad) * radius;
                float py = y + sin(rad) * radius;

                parts[p][i].setSize({ 12.f, thickness });
                parts[p][i].setOrigin({ 6.f, thickness / 2.f });
                parts[p][i].setPosition({ px, py });
                parts[p][i].setRotation(sf::degrees(angle + 90.f));
                parts[p][i].setFillColor(colors[p]);
            }
        }
    }

    void draw(sf::RenderWindow& window) override
    {
        for (int p = 0; p < 4; p++)
            for (int i = 0; i < SEGMENTS; i++)
                window.draw(parts[p][i]);
    }
};

class RectangleShapeObj : public Shape
{
private:
    sf::RectangleShape top, bottom, left, right;

public:
    RectangleShapeObj(float x, float y)
    {
        float size = 250.f;
        float thick = 20.f;

        top.setSize({ size, thick });
        bottom.setSize({ size, thick });
        left.setSize({ thick, size });
        right.setSize({ thick, size });

        top.setOrigin({ size / 2.f, thick / 2.f });
        bottom.setOrigin({ size / 2.f, thick / 2.f });
        left.setOrigin({ thick / 2.f, size / 2.f });
        right.setOrigin({ thick / 2.f, size / 2.f });

        top.setPosition({ x, y - size / 2.f });
        bottom.setPosition({ x, y + size / 2.f });
        left.setPosition({ x - size / 2.f + thick / 2.f, y });
        right.setPosition({ x + size / 2.f - thick / 2.f, y });

        sf::Color colors[4];
        getShuffledColors(colors);
        top.setFillColor(colors[0]);
        bottom.setFillColor(colors[1]);
        left.setFillColor(colors[2]);
        right.setFillColor(colors[3]);
    }

    void draw(sf::RenderWindow& window) override
    {
        window.draw(left);
        window.draw(right);
        window.draw(top);
        window.draw(bottom);
    }
};

class TriangleShapeObj : public Shape
{
private:
    sf::RectangleShape left, right, bottom;
    float centerX, centerY;

public:
    TriangleShapeObj(float x, float y)
    {
        centerX = x;
        centerY = y;
        float base = 260.f;
        float thickness = 20.f;
        float angle = 60.f;

        // Correct side length (same as base for equilateral triangle)
        float sideLength = base + 5.f;

        sf::Color colors[4];
        getShuffledColors(colors);

        float baseY = y + 80.f;

        // Bottom
        bottom.setSize({ base, thickness });
        bottom.setOrigin({ base / 2.f, thickness / 2.f });
        bottom.setPosition({ x, baseY });
        bottom.setFillColor(colors[0]);

        // Left side
        left.setSize({ sideLength, thickness });
        left.setOrigin({ 0.f, thickness / 2.f });
        left.setPosition({ x - base / 2.f, baseY });
        left.setRotation(sf::degrees(-angle));
        left.setFillColor(colors[1]);

        // Right side
        right.setSize({ sideLength, thickness });
        right.setOrigin({ sideLength, thickness / 2.f });
        right.setPosition({ x + base / 2.f, baseY });
        right.setRotation(sf::degrees(angle));
        right.setFillColor(colors[2]);
    }

    void draw(sf::RenderWindow& window) override
    {
        window.draw(left);
        window.draw(right);
        window.draw(bottom);
    }
};

class HorizontalLine : public Shape
{
private:
    sf::RectangleShape parts[4];

public:
    HorizontalLine(float y, float width)
    {
        float segmentWidth = width / 4.f;
        sf::Color colors[4];
        getShuffledColors(colors);

        for (int i = 0; i < 4; i++)
        {
            parts[i].setSize({ segmentWidth, 20.f });
            parts[i].setFillColor(colors[i]);
            parts[i].setOrigin({ segmentWidth / 2.f, 10.f });
            parts[i].setPosition({
                segmentWidth / 2.f + i * segmentWidth, y
                });
        }
    }

    void draw(sf::RenderWindow& window) override
    {
        for (int i = 0; i < 4; i++)
            window.draw(parts[i]);
    }
};

class PlusShape : public Shape
{
private:
    sf::RectangleShape left, right, top, bottom;

public:
    PlusShape(float x, float y, float size)
    {
        float thickness = 20.f;
        float half = size / 2.f;

        sf::Color colors[4];
        getShuffledColors(colors);

        left.setSize({ half, thickness });
        left.setOrigin({ half, thickness / 2.f });
        left.setPosition({ x, y });
        left.setFillColor(colors[0]);

        right.setSize({ half, thickness });
        right.setOrigin({ 0.f, thickness / 2.f });
        right.setPosition({ x, y });
        right.setFillColor(colors[1]);

        top.setSize({ thickness, half });
        top.setOrigin({ thickness / 2.f, half });
        top.setPosition({ x, y });
        top.setFillColor(colors[2]);

        bottom.setSize({ thickness, half });
        bottom.setOrigin({ thickness / 2.f, 0.f });
        bottom.setPosition({ x, y });
        bottom.setFillColor(colors[3]);
    }

    void draw(sf::RenderWindow& window) override
    {
        window.draw(top);
        window.draw(bottom);
        window.draw(left);
        window.draw(right);
    }
};

class StarCollectible : public Shape
{
private:
    sf::Texture texture;
    sf::Sprite* sprite;

public:
    StarCollectible(float x, float y)
    {
        if (!texture.loadFromFile("ColorSwitchSprites/Star.png"))
            cout << "Star NOT loaded\n";

        sprite = new sf::Sprite(texture);
        sf::FloatRect bounds = sprite->getLocalBounds();
        sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
        sprite->setScale({ 0.3f, 0.3f });
        sprite->setPosition({ x, y });
    }

    ~StarCollectible() { delete sprite; }

    void draw(sf::RenderWindow& window) override
    {
        window.draw(*sprite);
    }
};

class Ball
{
private:
    sf::CircleShape circle;
    float velocityY;

public:
    Ball(float radius, float startX, float startY)
    {
        circle.setRadius(radius);
        circle.setFillColor(sf::Color(128, 213, 111));
        circle.setOrigin({ radius, radius });
        circle.setPosition({ startX, startY });
        velocityY = 0.f;
    }

    void draw(sf::RenderWindow& window) { window.draw(circle); }
    void setPosition(float x, float y) { circle.setPosition({ x, y }); }
    sf::Vector2f getPosition() const { return circle.getPosition(); }
    void move(float dx, float dy) { circle.move({ dx, dy }); }
    void setVelocityY(float v) { velocityY = v; }
    float getVelocityY() const { return velocityY; }
    void addVelocityY(float value) { velocityY += value; }
};

class Camera
{
private:
    sf::View view;
    float cameraVelocity;
    float cameraFollowSpeed;

public:
    Camera(float width, float height)
        : view(sf::FloatRect({ 0.f, 0.f }, { width, height }))
    {
        cameraVelocity = 0.f;
        cameraFollowSpeed = 0.04f;
    }

    sf::View& getView() { return view; }
    float getCameraVelocity() const { return cameraVelocity; }
    void  setCameraVelocity(float v) { cameraVelocity = v; }
    float getCameraFollowSpeed() const { return cameraFollowSpeed; }
    void  move(float dx, float dy) { view.move({ dx, dy }); }
    void  setCenter(float x, float y) { view.setCenter({ x, y }); }
    sf::Vector2f getCenter() const { return view.getCenter(); }
};


void resizeArray(Shape**& shapes, int& capacity);
void addShape(Shape**& shapes, int& count, int& capacity, Shape* newShape);
void spawnShape(Shape**& shapes, int& count, int& capacity, float x, float y, float width);
void removeFirst(Shape**& shapes, int& count);
void applyGravity(Ball& ball, float gravity);
void moveBall(Ball& ball);
void resetBallOnGround(Ball& ball, float groundY);
void updateCamera(Camera& camera, Ball& ball, int width, int height);