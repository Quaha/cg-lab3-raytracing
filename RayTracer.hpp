#pragma once

#include <vector>

#include "geometry.hpp"
#include "Camera.hpp"
#include "Primitive.hpp"
#include "Material.hpp"
#include "Light.hpp"

class RayTracer {
private:

	const unsigned int width;
	const unsigned int height;

	std::vector<Primitive> objects;
	std::vector<Camera> cameras;
	std::vector<Light> lights;

	Vector3f ambient_light = Vector3f(0.1f, 0.1f, 0.1f);
	Vector3f background_color = Vector3f(0.2f, 0.7f, 0.8f);

private:
	Primitive& detectNearestObject(const Ray& ray);
	Vector3f castRay(const Ray& ray);

	void initObjects();
	void initCameras();
	void initLights();

public:

	RayTracer(unsigned int width, unsigned int height);

	void render();
};