#pragma once

#include "Camera.hpp"

class RayTracer {
private:

	const unsigned int width;
	const unsigned int height;

	Camera camera;

public:

	RayTracer(unsigned int width,
			  unsigned int height);

	void render();

	void saveAsPNG(std::vector<Vector3f> frame_buffer);
	void saveAsPNG(std::vector<Vector4f> frame_buffer);
};