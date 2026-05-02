#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
private:
    sf::View view;
    float cameraVelocity;
    float cameraFollowSpeed;

public:
    Camera(float width, float height);

    sf::View& getView();
    float getCameraVelocity() const;

    void setCameraVelocity(float v);
    float getCameraFollowSpeed() const;

    void move(float dx, float dy);
    void setCenter(float x, float y);
    sf::Vector2f getCenter() const;
};