#pragma once

#include <vector>

#include "Primitive.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class SceneManager {
private:

	const unsigned int width;
	const unsigned int height;

	std::vector<Primitive> objects;
	std::vector<Camera> cameras;
	std::vector<Light> lights;

	void initObjects();
	void initCameras();
	void initLights();

public:

	SceneManager(unsigned int width, unsigned int height);

	void render();

};