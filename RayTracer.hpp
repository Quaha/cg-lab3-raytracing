#pragma once

#include <vector>

#include "geometry.hpp"
#include "Camera.hpp"
#include "Primitive.hpp"
#include "Material.hpp"

class RayTracer {
private:

	const unsigned int width;
	const unsigned int height;

	std::vector<Primitive> objects;
	std::vector<Camera> cameras;

	Vector3f background_color;

private:
	Primitive& detectNearestObject(const Ray& ray);
	Vector3f castRay(const Ray& ray);

	void initObjects();
	void initCameras();

public:

	RayTracer(unsigned int width, unsigned int height);

	void render();
};