#pragma once

#include "geometry.hpp"

class Camera {
private:
    Vector3f position;
    float yaw;   // Around Y
    float pitch; // Up-Down

    //The Y - axis is pointing downwards when displayed.

    float FOV;

    Vector3f forward;
    Vector3f right;
    Vector3f up;

    void updateVectors();

public:
    Camera(const Vector3f& position, const Vector3f& target, float FOV);

    void rotate(float yaw_delta, float pitch_delta);

    Vector3f getPosition() const;

    Vector3f getForward() const;
    Vector3f getRight() const;
    Vector3f getUp() const;

    float getFOV() const;
};
