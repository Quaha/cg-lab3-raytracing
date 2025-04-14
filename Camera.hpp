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

	Camera(float xp, float yp, float zp,
		   const Vector3f& direction,
		   float FOV);
	

	Camera(const Vector3f& position,
		   float xd, float yd, float zd,
		   float FOV);
	

	Camera(float xp, float yp, float zp,
		   float xd, float yd, float zd,
		   float FOV);
	

	void setPosition(const Vector3f& position);
	void setPosition(float x, float y, float z);
	Vector3f getPosition() const;

	void setDirection(const Vector3f& position);
	void setDirection(float x, float y, float z);
	Vector3f getDirection() const;

	void setFOV(float FOV);
	float getFOV() const;

};