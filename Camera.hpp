#pragma once

#include "geometry.hpp"

class Camera {
private:

	Vector3f position;
	float FOV;

	Vector3f FORWARD = Vector3f(0.0f, 0.0f, -1.0f);
	Vector3f RIGHT = Vector3f(-1.0f, 0.0f, 0.0f);
	Vector3f UP = Vector3f(0.0f, 1.0f, 0.0f);

	float xz_angle = 0.0f;
	float y_angle = 0.0f;

public:

	Camera() = default;

	Camera(const Vector3f& position, float FOV);

	void setPosition(const Vector3f& position);
	void setPosition(float x, float y, float z);
	Vector3f getPosition() const;

	void setFOV(float FOV);
	float getFOV() const;

	Vector3f getForward() const;
	Vector3f getRight() const;
	Vector3f getUp() const;

	void rotateXZ(float angle);
	void rotateY(float angle);
};