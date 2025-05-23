#include <vector>
#include <format>

#include "SceneManager.hpp"

#include "geometry.hpp"
#include "Camera.hpp"
#include "Primitive.hpp"
#include "Light.hpp"
#include "PNGsaver.hpp"
#include "RayTracer.hpp"

void initObjects1(std::vector<Primitive>& objects) {

    Material red_surface(Vector3f(0.8f, 0.0f, 0.0f), 1.0f, 200, 1.5f, true, 0.1f, true, 0.1f, 1.5f);
    Material green_surface(Vector3f(0.2f, 0.7f, 0.3f), 1.0f, 5, 0.1f, false, 0.0f, false, 0.0f, 0.0f);
    Material blue_surface(Vector3f(0.1f, 0.1f, 0.8f), 1.0f, 60, 0.2f, false, 0.0f, false, 0.0f, 0.0f);

    Material reflector_surface(Vector3f(0.0f, 0.0f, 0.0f), 0.0f, 500, 5.0f, true, 0.85f, false, 0.0f, 0.0f);

    Material glass_surface(Vector3f(0.0f, 0.0f, 0.0f), 0.0f, 50, 0.3f, true, 0.07f, true, 0.85f, 1.5f);

    objects.push_back(Primitive(Vector3f(-0.5f, 0.2f, 0.3f), 0.33f, red_surface));
    objects.push_back(Primitive(Vector3f(0.3f, 0.2f, 0.0f), 0.25f, blue_surface));
    objects.push_back(Primitive(Vector3f(0.0f, 0.0f, -0.5f), 0.5f, green_surface));

    objects.push_back(Primitive(Vector3f(1.2f, -0.1f, -0.36f), 0.4f, reflector_surface));
    objects.push_back(Primitive(Vector3f(-1.3f, -0.3f, 0.27f), 0.34f, reflector_surface));

    //objects.push_back(Primitive(Vector3f(0.0f, 1.0f, 0.0f), Vector3f(1.0f, 1.0f, 0.0f), Vector3f(0.0f, 1.0f, 1.0f), red_surface));
}

void initCameras1(std::vector<Camera>& cameras) {

    Camera camera1(Vector3f(0.0f, 0.0f, 2.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        degreesToRadians(60.0f));

    cameras.push_back(camera1);

    Camera camera2(Vector3f(-1.0f, -3.0f, -1.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        degreesToRadians(60.0f));

    cameras.push_back(camera2);

    Camera camera3(Vector3f(-1.0f, 3.0f, -2.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        degreesToRadians(60.0f));

    cameras.push_back(camera3);
}

void initLights1(std::vector<Light>& lights) {
    lights.push_back(Light(Vector3f(2.0f, -2.2f, 2.0f), 0.8f, Vector3f(1.0f, 1.0f, 1.0f)));
    lights.push_back(Light(Vector3f(0.0f, 3.0f, 0.0f), 0.8f, Vector3f(1.0f, 0.1f, 0.1f)));
    lights.push_back(Light(Vector3f(-2.0f, 0.0f, 2.0f), 0.8f, Vector3f(1.0f, 1.0f, 1.0f)));
}

void SceneManager::loadScene(size_t scene_id, const std::string& title) {
    switch (scene_id) {
    case 0:
        initObjects1(objects);
        initCameras1(cameras);
        initLights1(lights);

        this->title = title;
        break;

    default:
        assert(false);
        break;
    }
}

void SceneManager::clearScene() {
    objects.clear();
    cameras.clear();
    lights.clear();

    title = "";
}

void SceneManager::renderPhotos(unsigned int width, unsigned int height) {

    for (size_t k = 0; k < cameras.size(); ++k) {
        const Camera& camera = cameras[k];
        std::vector<Vector3f> frame_buffer(width * height);

        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {

                /*
                * 1. xp = (j + 0.5) / width: j in [0, width] -> [0, 1]
                * 2. (2 * xp - 1): xp in [0, 1] -> xp in [-1, 1]
                * 3. xp *  tan(camera.getFOV() / 2): Conversion depending on FOV
                * 4. width / heigh: Correction due to differences in the sides
                */

                float scale = tan(camera.getFOV() / 2.0f);
                float screen_aspect_ratio = width / (float)height;

                float x = (2 * (j + 0.5f) / (float)width - 1) * scale * screen_aspect_ratio;
                float y = (2 * (i + 0.5f) / (float)height - 1) * scale;

                Vector3f direction = (camera.getRight() * x +
                    camera.getUp() * y +
                    camera.getForward()).normalize();

                Ray ray(camera.getPosition(), direction);
                frame_buffer[j + i * width] = RayTracer::castRay(ray, objects, lights);
            }
        }
        PNGsaver::saveAsPNG(std::format("{}_{}.png", title, k + 1), frame_buffer, width, height);
        std::cout << "Rendering Time (ms): " << std::clock() << std::endl;
    }
}