#pragma once

#include <vector>
#include <string>

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

	std::string scene_name;

public:
	SceneManager(unsigned int width, unsigned int height);

	void loadScene(size_t scene_id, const std::string& scene_name);
	void clearScene();

	void render();

};