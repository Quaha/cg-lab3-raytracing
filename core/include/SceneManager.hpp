#pragma once

#include <vector>
#include <string>

#include "Primitive.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class SceneManager {
private:

	std::vector<Primitive> objects;
	std::vector<Camera> cameras;
	std::vector<Light> lights;

	std::string title;

public:

	SceneManager() = default;

	void loadScene(size_t scene_id, const std::string& title);
	void clearScene();

	void renderPhotos(unsigned int width, unsigned int height);
};