#include "Camera.h"

Camera::Camera(float width, float height)
    : view(sf::FloatRect({ 0.f, 0.f }, { width, height }))
{
    cameraVelocity = 0.f;
    cameraFollowSpeed = 0.04f;
}

sf::View& Camera::getView() { return view; }

float Camera::getCameraVelocity() const { return cameraVelocity; }

void Camera::setCameraVelocity(float v) { cameraVelocity = v; }

float Camera::getCameraFollowSpeed() const { return cameraFollowSpeed; }

void Camera::move(float dx, float dy) { view.move({ dx, dy }); }

void Camera::setCenter(float x, float y) { view.setCenter({ x, y }); }

sf::Vector2f Camera::getCenter() const { return view.getCenter(); }