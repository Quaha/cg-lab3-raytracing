#pragma once

#include <vector>

#include "geometry.hpp"
#include "Camera.hpp"
#include "Primitive.hpp"

class RayTracer {
private:

	const unsigned int width;
	const unsigned int height;

	Camera camera;

	std::vector<Primitive> objects;

	Vector3f background_color;

private:
	Primitive& detectNearestObject(const Ray& ray);
	Vector3f castRay(const Ray& ray);

	void initObjects();

	void saveAsPNG(std::vector<Vector3f> frame_buffer) const;
	void saveAsPNG(std::vector<Vector4f> frame_buffer) const;

public:

	RayTracer(unsigned int width,
			  unsigned int height);

	void render();
};