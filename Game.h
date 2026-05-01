//#pragma once
//#include <SFML/Graphics.hpp>
//#include <cstdlib>
//#include <ctime>
//#include <cmath>
//#include <iostream>
//#include "MathUtils.h"
//
//using namespace std;
//extern sf::Color palette[4];
//void getShuffledColors(sf::Color colors[4]);
//
//class Shape
//{
//protected:
//    float posY = 0.f;
//    float halfHeight = 0.f;
//    bool passed = false;
//    bool collected = false;
//
//public:
//    virtual void draw(sf::RenderWindow& window) = 0;
//    virtual void rotateShape(float angle) {}
//
//    virtual bool isObstacle() const
//    {
//        return true;
//    }
//    virtual bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const
//    {
//        float topEdge = posY - halfHeight;
//        float bottomEdge = posY + halfHeight;
//
//        return ballPos.y + ballRadius > topEdge &&
//            ballPos.y - ballRadius < bottomEdge;
//    }
//    bool isCollected() const
//    {
//        return collected;
//    }
//
//    void markCollected()
//    {
//        collected = true;
//    }
//    virtual float getX() const { return 0.f; }
//
//    virtual sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const
//    {
//        return sf::Color::White;
//    }
//    virtual sf::Color getRandomAllowedColor() const
//    {
//        sf::Color colors[4] =
//        {
//            sf::Color(50, 226, 241),   // Cyan
//            sf::Color(255, 232, 15),   // Yellow
//            sf::Color(140, 18, 251),   // Purple
//            sf::Color(255, 0, 128)     // Pink
//        };
//
//        return colors[rand() % 4];
//    }
//    float getY() const { return posY; }
//    float getHalfHeight() const { return halfHeight; }
//
//    bool isPassed() const { return passed; }
//    void markPassed() { passed = true; }
//
//    virtual ~Shape() {}
//};
//class CircleShapeObj : public Shape
//{
//private:
//    static const int SEGMENTS = 40;
//    sf::RectangleShape parts[4][SEGMENTS];
//    sf::Color sectionColors[4];
//
//    float centerX, centerY;
//    float currentRotation = 0.f;
//
//public:
//    CircleShapeObj(float x, float y)
//    {
//        posY = y;
//        centerX = x;
//        centerY = y;
//        halfHeight = 170.f;
//
//        float radius = 150.f;
//        float thickness = 20.f;
//
//        sf::Color colors[4];
//        getShuffledColors(colors);
//
//        for (int i = 0; i < 4; i++)
//        {
//            sectionColors[i] = colors[i];
//        }
//
//        for (int p = 0; p < 4; p++)
//        {
//            for (int i = 0; i < SEGMENTS; i++)
//            {
//                float angle = (p * 90.f) + (i * (90.f / SEGMENTS));
//                float rad = angle * 3.14159265f / 180.f;
//
//                float px = x + cos(rad) * radius;
//                float py = y + sin(rad) * radius;
//
//                parts[p][i].setSize({ 12.f, thickness });
//                parts[p][i].setOrigin({ 6.f, thickness / 2.f });
//                parts[p][i].setPosition({ px, py });
//                parts[p][i].setRotation(sf::degrees(angle + 90.f));
//                parts[p][i].setFillColor(sectionColors[p]);
//            }
//        }
//    }
//    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override
//    {
//        float dx = ballPos.x - centerX;
//        float dy = ballPos.y - centerY;
//
//        float distance = std::sqrt(dx * dx + dy * dy);
//
//        float outerRadius = 160.f;
//        float innerRadius = 135.f;
//
//        return distance + ballRadius >= innerRadius &&
//            distance - ballRadius <= outerRadius;
//    }
//    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override
//    {
//        sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);
//
//        float angle = atan2(local.y, local.x) * 180.f / 3.14159265f;
//
//        if (angle < 0)
//            angle += 360.f;
//
//        int section = static_cast<int>(angle / 90.f);
//
//        return sectionColors[section];
//    }
//
//    void rotateShape(float angle) override
//    {
//        currentRotation += angle;
//    }
//
//    void draw(sf::RenderWindow& window) override
//    {
//        sf::RenderStates states;
//        states.transform.translate({ centerX, centerY });
//        states.transform.rotate(sf::degrees(currentRotation));
//        states.transform.translate({ -centerX, -centerY });
//
//        for (int p = 0; p < 4; p++)
//        {
//            for (int i = 0; i < SEGMENTS; i++)
//            {
//                window.draw(parts[p][i], states);
//            }
//        }
//    }
//};
//class RectangleShapeObj : public Shape
//{
//private:
//    sf::RectangleShape top, bottom, left, right;
//    sf::Color colorTop, colorBottom, colorLeft, colorRight;
//
//    float centerX, centerY;
//    float currentRotation = 0.f;
//
//public:
//    RectangleShapeObj(float x, float y)
//    {
//        posY = y;
//        centerX = x;
//        centerY = y;
//        halfHeight = 140.f;
//
//        float size = 250.f;
//        float thick = 20.f;
//
//        top.setSize({ size, thick });
//        bottom.setSize({ size, thick });
//        left.setSize({ thick, size });
//        right.setSize({ thick, size });
//
//        top.setOrigin({ size / 2.f, thick / 2.f });
//        bottom.setOrigin({ size / 2.f, thick / 2.f });
//        left.setOrigin({ thick / 2.f, size / 2.f });
//        right.setOrigin({ thick / 2.f, size / 2.f });
//
//        top.setPosition({ x, y - size / 2.f });
//        bottom.setPosition({ x, y + size / 2.f });
//        left.setPosition({ x - size / 2.f + thick / 2.f, y });
//        right.setPosition({ x + size / 2.f - thick / 2.f, y });
//
//        sf::Color colors[4];
//        getShuffledColors(colors);
//        colorTop = colors[0];
//        colorBottom = colors[1];
//        colorLeft = colors[2];
//        colorRight = colors[3];
//        top.setFillColor(colors[0]);
//        bottom.setFillColor(colors[1]);
//        left.setFillColor(colors[2]);
//        right.setFillColor(colors[3]);
//    }
//    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override
//    {
//        sf::Vector2f local =
//            rotatePointBack(ballPos, centerX, centerY, currentRotation);
//
//        float halfSize = 125.f;
//        float thick = 20.f;
//
//        bool touchTop =
//            local.y + ballRadius >= -halfSize &&
//            local.y - ballRadius <= -halfSize + thick &&
//            local.x >= -halfSize &&
//            local.x <= halfSize;
//
//        bool touchBottom =
//            local.y + ballRadius >= halfSize - thick &&
//            local.y - ballRadius <= halfSize &&
//            local.x >= -halfSize &&
//            local.x <= halfSize;
//
//        bool touchLeft =
//            local.x + ballRadius >= -halfSize &&
//            local.x - ballRadius <= -halfSize + thick &&
//            local.y >= -halfSize &&
//            local.y <= halfSize;
//
//        bool touchRight =
//            local.x + ballRadius >= halfSize - thick &&
//            local.x - ballRadius <= halfSize &&
//            local.y >= -halfSize &&
//            local.y <= halfSize;
//
//        return touchTop || touchBottom || touchLeft || touchRight;
//    }
//    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override
//    {
//        sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);
//
//        if (std::abs(local.x) > std::abs(local.y))
//            return local.x < 0 ? colorLeft : colorRight;
//        else
//            return local.y < 0 ? colorTop : colorBottom;
//    }
//
//
//    void rotateShape(float angle) override
//    {
//        currentRotation += angle;
//    }
//
//    void draw(sf::RenderWindow& window) override
//    {
//        sf::RenderStates states;
//        states.transform.translate({ centerX, centerY });
//        states.transform.rotate(sf::degrees(currentRotation));
//        states.transform.translate({ -centerX, -centerY });
//
//        window.draw(left, states);
//        window.draw(right, states);
//        window.draw(top, states);
//        window.draw(bottom, states);
//    }
//};
//
//class TriangleShapeObj : public Shape
//{
//private:
//    sf::RectangleShape left, right, bottom;
//
//    sf::Color leftColor;
//    sf::Color rightColor;
//    sf::Color bottomColor;
//
//    float centerX, centerY;
//    float currentRotation = 0.f;
//
//public:
//    TriangleShapeObj(float x, float y)
//    {
//        posY = y;
//        centerX = x;
//        centerY = y;
//        halfHeight = 150.f;
//
//        float base = 260.f;
//        float thickness = 20.f;
//        float angle = 60.f;
//        float sideLength = base + 5.f;
//
//        sf::Color colors[4];
//        getShuffledColors(colors);
//
//        bottomColor = colors[0];
//        leftColor = colors[1];
//        rightColor = colors[2];
//
//        float baseY = y + 80.f;
//
//        bottom.setSize({ base, thickness });
//        bottom.setOrigin({ base / 2.f, thickness / 2.f });
//        bottom.setPosition({ x, baseY });
//        bottom.setFillColor(bottomColor);
//
//        left.setSize({ sideLength, thickness });
//        left.setOrigin({ 0.f, thickness / 2.f });
//        left.setPosition({ x - base / 2.f, baseY });
//        left.setRotation(sf::degrees(-angle));
//        left.setFillColor(leftColor);
//
//        right.setSize({ sideLength, thickness });
//        right.setOrigin({ sideLength, thickness / 2.f });
//        right.setPosition({ x + base / 2.f, baseY });
//        right.setRotation(sf::degrees(angle));
//        right.setFillColor(rightColor);
//    }
//
//    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override
//    {
//        sf::Vector2f local =
//            rotatePointBack(ballPos, centerX, centerY, currentRotation);
//
//        float baseY = 80.f;
//        float thickness = 20.f;
//        float halfBase = 130.f;
//
//        bool touchBottom =
//            local.y + ballRadius >= baseY - thickness / 2.f &&
//            local.y - ballRadius <= baseY + thickness / 2.f &&
//            local.x >= -halfBase &&
//            local.x <= halfBase;
//
//        float leftSideX =
//            -halfBase + ((local.y + 130.f) / 210.f) * halfBase;
//
//        float rightSideX =
//            halfBase - ((local.y + 130.f) / 210.f) * halfBase;
//
//        bool touchLeft =
//            local.y >= -130.f &&
//            local.y <= baseY &&
//            std::abs(local.x - leftSideX) <= thickness + ballRadius;
//
//        bool touchRight =
//            local.y >= -130.f &&
//            local.y <= baseY &&
//            std::abs(local.x - rightSideX) <= thickness + ballRadius;
//
//        return touchBottom || touchLeft || touchRight;
//    }
//
//    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override
//    {
//        sf::Vector2f local =
//            rotatePointBack(ballPos, centerX, centerY, currentRotation);
//
//        float baseY = 80.f;
//        float thickness = 20.f;
//        float halfBase = 130.f;
//
//        bool touchBottom =
//            local.y >= baseY - thickness * 2.f;
//
//        float leftSideX =
//            -halfBase + ((local.y + 130.f) / 210.f) * halfBase;
//
//        float rightSideX =
//            halfBase - ((local.y + 130.f) / 210.f) * halfBase;
//
//        if (touchBottom)
//            return bottomColor;
//
//        if (std::abs(local.x - leftSideX) <
//            std::abs(local.x - rightSideX))
//            return leftColor;
//
//        return rightColor;
//    }
//
//    sf::Color getRandomAllowedColor() const override
//    {
//        int r = rand() % 3;
//
//        if (r == 0)
//            return bottomColor;
//        else if (r == 1)
//            return leftColor;
//        else
//            return rightColor;
//    }
//
//    void rotateShape(float angle) override
//    {
//        currentRotation += angle;
//    }
//
//    void draw(sf::RenderWindow& window) override
//    {
//        sf::RenderStates states;
//
//        states.transform.translate({ centerX, centerY });
//        states.transform.rotate(sf::degrees(currentRotation));
//        states.transform.translate({ -centerX, -centerY });
//
//        window.draw(left, states);
//        window.draw(right, states);
//        window.draw(bottom, states);
//    }
//};
//class HorizontalLine : public Shape
//{
//private:
//    sf::RectangleShape parts[8]; // 2 full lines, 4 segments each
//    sf::Color segmentColors[4];
//    float offset = 0.f;
//    float speed = 2.5f;
//    float width;
//    float y;
//
//public:
//    HorizontalLine(float y, float width)
//    {
//        posY = y;
//        this->width = width;
//        this->y = y;
//        halfHeight = 20.f;
//
//        float segmentWidth = width / 4.f;
//
//        sf::Color colors[4];
//        getShuffledColors(colors);
//
//        for (int i = 0; i < 4; i++)
//        {
//            segmentColors[i] = colors[i];
//        }
//
//        for (int copy = 0; copy < 2; copy++)
//        {
//            for (int i = 0; i < 4; i++)
//            {
//                int index = copy * 4 + i;
//
//                parts[index].setSize({ segmentWidth, 20.f });
//                parts[index].setOrigin({ segmentWidth / 2.f, 10.f });
//                parts[index].setFillColor(segmentColors[i]);
//            }
//        }
//    }
//    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override
//    {
//        return ballPos.y + ballRadius >= y - 10.f &&
//            ballPos.y - ballRadius <= y + 10.f;
//    }
//    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override
//    {
//        float segmentWidth = width / 4.f;
//
//        float adjustedX = ballPos.x - offset;
//
//        while (adjustedX < 0)
//            adjustedX += width;
//
//        while (adjustedX >= width)
//            adjustedX -= width;
//
//        int section = static_cast<int>(adjustedX / segmentWidth);
//
//        return segmentColors[section];
//    }
//    void rotateShape(float angle) override
//    {
//        offset += speed;
//
//        if (offset >= width)
//            offset = 0.f;
//
//        float segmentWidth = width / 4.f;
//
//        for (int copy = 0; copy < 2; copy++)
//        {
//            float copyOffset = offset - copy * width;
//
//            for (int i = 0; i < 4; i++)
//            {
//                int index = copy * 4 + i;
//
//                float x = segmentWidth / 2.f + i * segmentWidth + copyOffset;
//                parts[index].setPosition({ x, y });
//            }
//        }
//    }
//
//    void draw(sf::RenderWindow& window) override
//    {
//        for (int i = 0; i < 8; i++)
//            window.draw(parts[i]);
//    }
//};
//class PlusShape : public Shape
//{
//private:
//    sf::RectangleShape left, right, top, bottom;
//
//    sf::Color leftColor, rightColor, topColor, bottomColor;
//
//    float centerX, centerY;
//    float currentRotation = 0.f;
//    float rotationDirection;
//
//public:
//    PlusShape(float x, float y, float size, float direction)
//    {
//        posY = y;
//        halfHeight = 90.f;
//
//        centerX = x;
//        centerY = y;
//        rotationDirection = direction;
//
//        float thickness = 20.f;
//        float half = size / 2.f;
//
//        sf::Color colors[4];
//        getShuffledColors(colors);
//
//        leftColor = colors[0];
//        rightColor = colors[1];
//        topColor = colors[2];
//        bottomColor = colors[3];
//
//        left.setSize({ half, thickness });
//        left.setOrigin({ half, thickness / 2.f });
//        left.setPosition({ x, y });
//        left.setFillColor(leftColor);
//
//        right.setSize({ half, thickness });
//        right.setOrigin({ 0.f, thickness / 2.f });
//        right.setPosition({ x, y });
//        right.setFillColor(rightColor);
//
//        top.setSize({ thickness, half });
//        top.setOrigin({ thickness / 2.f, half });
//        top.setPosition({ x, y });
//        top.setFillColor(topColor);
//
//        bottom.setSize({ thickness, half });
//        bottom.setOrigin({ thickness / 2.f, 0.f });
//        bottom.setPosition({ x, y });
//        bottom.setFillColor(bottomColor);
//    }
//    bool isBallTouching(sf::Vector2f ballPos, float ballRadius) const override
//    {
//        sf::Vector2f local =
//            rotatePointBack(ballPos, centerX, centerY, currentRotation);
//
//        float armLength = 90.f;
//        float thick = 20.f;
//
//        bool horizontal =
//            local.x + ballRadius >= -armLength &&
//            local.x - ballRadius <= armLength &&
//            local.y + ballRadius >= -thick / 2.f &&
//            local.y - ballRadius <= thick / 2.f;
//
//        bool vertical =
//            local.x + ballRadius >= -thick / 2.f &&
//            local.x - ballRadius <= thick / 2.f &&
//            local.y + ballRadius >= -armLength &&
//            local.y - ballRadius <= armLength;
//
//        return horizontal || vertical;
//    }
//    sf::Color getCurrentTouchColor(sf::Vector2f ballPos) const override
//    {
//        sf::Vector2f local = rotatePointBack(ballPos, centerX, centerY, currentRotation);
//
//        if (std::abs(local.x) > std::abs(local.y))
//            return local.x < 0 ? leftColor : rightColor;
//        else
//            return local.y < 0 ? topColor : bottomColor;
//    }
//    void rotateShape(float angle) override
//    {
//        currentRotation += angle * rotationDirection;
//    }
//
//  
//
//    void draw(sf::RenderWindow& window) override
//    {
//        sf::RenderStates states;
//        states.transform.translate({ centerX, centerY });
//        states.transform.rotate(sf::degrees(currentRotation));
//        states.transform.translate({ -centerX, -centerY });
//
//        window.draw(top, states);
//        window.draw(bottom, states);
//        window.draw(left, states);
//        window.draw(right, states);
//    }
//};
//class StarCollectible : public Shape
//{
//private:
//    sf::Texture texture;
//    sf::Sprite* sprite;
//
//    float centerX;
//    float centerY;
//
//public:
//    StarCollectible(float x, float y)
//    {
//        centerX = x;
//        centerY = y;
//
//        posY = y; // base class usage
//
//        if (!texture.loadFromFile("ColorSwitchSprites/Star.png"))
//            std::cout << "Star NOT loaded\n";
//
//        sprite = new sf::Sprite(texture);
//
//        sf::FloatRect bounds = sprite->getLocalBounds();
//        sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
//        sprite->setScale({ 0.3f, 0.3f });
//        sprite->setPosition({ x, y });
//    }
//
//    bool isObstacle() const override
//    {
//        return false;
//    }
//
//    float getX() const override
//    {
//        return centerX;
//    }
//
//    float getY() const
//    {
//        return centerY;
//    }
//
//
//
//    void draw(sf::RenderWindow& window) override
//    {
//        window.draw(*sprite);
//    }
//
//    ~StarCollectible()
//    {
//        delete sprite;
//    }
//};
//
//class Ball
//{
//private:
//    sf::CircleShape circle;
//    float velocityY;
//
//public:
//    Ball(float radius, float startX, float startY)
//    {
//        circle.setRadius(radius);
//        circle.setOrigin({ radius, radius });
//        circle.setPosition({ startX, startY });
//
//        //  pick random color from your palette
//        circle.setFillColor(palette[rand() % 4]);
//
//        velocityY = 0.f;
//    }
//    void setRandomColor()
//    {
//        circle.setFillColor(palette[rand() % 4]);
//    }
//
//    float getRadius() const
//    {
//        return circle.getRadius();
//    }
//    sf::Color getColor() const
//    {
//        return circle.getFillColor();
//    }
//    void setColor(sf::Color newColor)
//    {
//        circle.setFillColor(newColor);
//    }
//    void draw(sf::RenderWindow& window) { window.draw(circle); }
//    void setPosition(float x, float y) { circle.setPosition({ x, y }); }
//    sf::Vector2f getPosition() const { return circle.getPosition(); }
//    void move(float dx, float dy) { circle.move({ dx, dy }); }
//    void setVelocityY(float v) { velocityY = v; }
//    float getVelocityY() const { return velocityY; }
//    void addVelocityY(float value) { velocityY += value; }
//};
//class Camera
//{
//private:
//    sf::View view;
//    float cameraVelocity;
//    float cameraFollowSpeed;
//
//public:
//    Camera(float width, float height)
//        : view(sf::FloatRect({ 0.f, 0.f }, { width, height }))
//    {
//        cameraVelocity = 0.f;
//        cameraFollowSpeed = 0.04f;
//    }
//
//    sf::View& getView() { return view; }
//    float getCameraVelocity() const { return cameraVelocity; }
//    void  setCameraVelocity(float v) { cameraVelocity = v; }
//    float getCameraFollowSpeed() const { return cameraFollowSpeed; }
//    void  move(float dx, float dy) { view.move({ dx, dy }); }
//    void  setCenter(float x, float y) { view.setCenter({ x, y }); }
//    sf::Vector2f getCenter() const { return view.getCenter(); }
//};
//#include"Collision.h"
//
//void resizeArray(Shape**& shapes, int& capacity);
//void addShape(Shape**& shapes, int& count, int& capacity, Shape* newShape);
//void spawnShape(Shape**& shapes, int& count, int& capacity, float x, float y, float width);
//void removeFirst(Shape**& shapes, int& count);
//void applyGravity(Ball& ball, float gravity);
//void moveBall(Ball& ball);
//void resetBallOnGround(Ball& ball, float groundY);
//void updateCamera(Camera& camera, Ball& ball, int width, int height);