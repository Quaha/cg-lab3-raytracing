#include "Camera.hpp"

Camera::Camera(
	const Vector3f& position,
	const Vector3f& direction,
	float FOV) : position(position), direction(direction), FOV(FOV) {}

Camera::Camera(
	float xp, float yp, float zp,
	const Vector3f& direction,
	float FOV) : direction(direction), FOV(FOV)
{
	position = Vector3f(xp, yp, zp);
}

Camera::Camera(
	const Vector3f& position,
	float xd, float yd, float zd,
	float FOV) : position(position), FOV(FOV)
{
	direction = Vector3f(xd, yd, zd);
}

Camera::Camera(
	float xp, float yp, float zp,
	float xd, float yd, float zd,
	float FOV) : FOV(FOV) 
{
	position = Vector3f(xp, yp, zp);
	direction = Vector3f(xp, yp, zp);
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

void Camera::setDirection(const Vector3f& position) {
	this->direction = position;
}

void Camera::setDirection(float x, float y, float z) {
	this->direction = Vector3f(x, y, z);
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