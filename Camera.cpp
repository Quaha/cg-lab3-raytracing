#include <cmath>

#include "Camera.hpp"

#include "geometry.hpp"

Camera::Camera(const Vector3f& position, const Vector3f& target, float FOV)
    : position(position), FOV(FOV)
{
    Vector3f direction = (target - position).normalize();

    yaw = atan2(direction.x, -direction.z);
    pitch = asin(-direction.y);

    updateVectors();
}

void Camera::updateVectors() {
    forward = Vector3f(sin(yaw) * cos(pitch),
                       -sin(pitch),
                       -cos(yaw) * cos(pitch)).normalize();

    right = cross(forward, Vector3f(0.0f, 1.0f, 0.0f)).normalize();
    up = cross(right, forward).normalize();
}

Vector3f Camera::getPosition() const {
    return position;
}

Vector3f Camera::getForward() const {
    return forward;
}

Vector3f Camera::getRight() const {
    return right;
}

Vector3f Camera::getUp() const {
    return up;
}

float Camera::getFOV() const {
    return FOV;
}

void Camera::rotate(float yaw_delta, float pitch_delta) {
    yaw += yaw_delta;
    pitch += pitch_delta;

    pitch = clamp(pitch, -PI / 2.0f, PI / 2.0f);
    updateVectors();
}
