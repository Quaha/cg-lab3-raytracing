#include "Camera.hpp"

#include "geometry.hpp"

Camera::Camera(const Vector3f& position, float FOV) {
	this->position = position;
	this->FOV = FOV;
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

void Camera::setFOV(float FOV) {
	this->FOV = FOV;
}

float Camera::getFOV() const {
	return FOV;
}

Vector3f Camera::getForward() const {
	return FORWARD;
}

Vector3f Camera::getRight() const {
	return RIGHT;
}

Vector3f Camera::getUp() const {
	return UP;
}

void Camera::rotateXZ(float angle) {
	xz_angle += clamp(angle, -360.0f, 360.0f);
	if (xz_angle < 0.0f) {
		xz_angle += 360.0f;
	}
	if (xz_angle > 360.0f) {
		xz_angle -= 360.0f;
	}
}

void Camera::rotateY(float angle) {
	angle = clamp(y_angle + angle, -89.0f, 89.0f);
}