#pragma once

#include "geometry.hpp"

class Camera {
private:

	Vector3f position;
	Vector3f direction;
	float FOV;

public:

	Camera() = default;

	Camera(const Vector3f& position,
		   const Vector3f& direction,
		   float FOV);

	void setPosition(const Vector3f& position);
	void setPosition(float x, float y, float z);
	Vector3f getPosition() const;

	void setDirection(const Vector3f& direction);
	void setDirection(float x, float y, float z);
	Vector3f getDirection() const;

	void setFOV(float FOV);
	float getFOV() const;
};