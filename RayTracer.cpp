#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <format>
#include <limits>

#include "RayTracer.hpp"

#include "geometry.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Primitive.hpp"
#include "PNGsaver.hpp"

void RayTracer::initObjects() {
    
    Material red_surface(Vector3f(0.67f, 0.1f, 0.14f));
    Material green_surface(Vector3f(0.2f, 0.7f, 0.3f));
    Material blue_surface(Vector3f(0.1f, 0.1f, 0.8f));

    this->objects.push_back(Primitive(Vector3f(-0.3f, 0.2f, 0.0f), 0.33f, red_surface));
    this->objects.push_back(Primitive(Vector3f(0.3f, 0.2f, 0.0f), 0.25f, blue_surface));
    this->objects.push_back(Primitive(Vector3f(0.0f, 0.0f, -0.5f), 0.5f, green_surface));
}

void RayTracer::initCameras() {

    Camera camera1(Vector3f(0.0f, 0.0f, 1.0f),
                   Vector3f(0.0f, 0.0f, 0.0f),
                   degreesToRadians(90.0f));

    this->cameras.push_back(camera1);

    Camera camera2(Vector3f(-1.0f, -3.0f, -1.0f),
                   Vector3f(0.0f, 0.0f, 0.0f),
                   degreesToRadians(90.0f));

    this->cameras.push_back(camera2);

    Camera camera3(Vector3f(-1.0f, 3.0f, -2.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        degreesToRadians(90.0f));

    this->cameras.push_back(camera3);
}

RayTracer::RayTracer(unsigned int width,
                     unsigned int height): width(width), height(height) {
    
    this->background_color = Vector3f(0.2f, 0.7f, 0.8f);

    initCameras();
    initObjects();
}

Primitive& RayTracer::detectNearestObject(const Ray& ray) {
    float lowest_dist = std::numeric_limits<float>::max();
    size_t nearest_object_id = 0;
    for (size_t i = 0; i < objects.size(); ++i) {
        float current_dist = std::numeric_limits<float>::max();
        objects[i].figure->processRayIntersect(ray, current_dist);

        if (current_dist < lowest_dist) {
            nearest_object_id = i;
            lowest_dist = current_dist;
        }
    }
    return objects[nearest_object_id];
}

Vector3f RayTracer::castRay(const Ray& ray) {
    if (objects.empty()) {
        return background_color;
    }
    float temp;
    const Primitive& nearest_object = detectNearestObject(ray);
    if (!nearest_object.figure->processRayIntersect(ray.start, ray.direction, temp)) {
        return background_color;
    }
    return nearest_object.material.color;
}


void RayTracer::render() {

    std::vector<Vector3f> frame_buffer(width * height);

    for (size_t k = 0; k < cameras.size(); ++k) {
        const Camera& camera = cameras[k];
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
                frame_buffer[j + i * width] = castRay(ray);
            }
        }
        PNGsaver::saveAsPNG(std::format("photo{}.png", k), frame_buffer, width, height);
    }
}