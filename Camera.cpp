#include "Camera.hpp"

#include "geometry.hpp"

Camera::Camera(
	const Vector3f& position,
	const Vector3f& direction,
	float FOV)
{
	this->position = position;
	this->direction = direction;
	this->FOV = FOV;

	this->direction.normalize();
}

void Camera::setPosition(const Vector3f& position) {
	this->position = position;
}

void Camera::setPosition(float x, float y, float z) {
	this->position = Vector3f(x, y, z);
}

Vector3f Camera::getPosition() const {
	return position;
}

void Camera::setDirection(const Vector3f& direction) {
	this->direction = direction;

	this->direction.normalize();
}

void Camera::setDirection(float x, float y, float z) {
	this->direction = Vector3f(x, y, z);

	this->direction.normalize();
}

Vector3f Camera::getDirection() const {
	return direction;
}

void Camera::setFOV(float FOV) {
	this->FOV = FOV;
}

float Camera::getFOV() const {
	return FOV;
}