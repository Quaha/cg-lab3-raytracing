#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

#include "RayTracer.hpp"
#include "geometry.hpp"
#include "Camera.hpp"

#include "lodepng.h"

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

void RayTracer::initObjects() {
    
    Material red_surface(Vector3f(0.67f, 0.1f, 0.14f));
    Material green_surface(Vector3f(0.2f, 0.7f, 0.3f));
    Material blue_surface(Vector3f(0.1f, 0.1f, 0.8f));

    this->objects.push_back(Primitive(Vector3f(-0.3f, -0.2f, -1.5f), 0.33f, red_surface));
    this->objects.push_back(Primitive(Vector3f(0.3f, -0.2f, -1.5f), 0.25f, blue_surface));
    this->objects.push_back(Primitive(Vector3f(0.0f, 0.0f, -2.0f), 0.5f, green_surface));
}

RayTracer::RayTracer(unsigned int width,
                     unsigned int height): width(width), height(height) {
    
    this->background_color = Vector3f(0.2f, 0.7f, 0.8f);

    this->camera = Camera(Vector3f(0, 0, 0), Vector3f(0, 0, 0), degreesToRadians(45.0f));

    initObjects();
}

void RayTracer::render() {

    std::vector<Vector3f> frame_buffer(width * height);

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            float x = (2 * (j) / (float)width - 1) * tan(camera.getFOV() / 2.0f) * width / (float)height;
            float y = -(2 * (i) / (float)height - 1) * tan(camera.getFOV() / 2.0f);
            Vector3f dir = Vector3f(x, y, -1).normalize();

            Ray ray(camera.getPosition(), dir);
            frame_buffer[j + i * width] = castRay(ray);
        }
    }

    saveAsPNG(frame_buffer);
}

void RayTracer::saveAsPNG(std::vector<Vector3f> frame_buffer) const{
    // Массив RGBA (lodepng требует 4 канала)
    std::vector<unsigned char> image(width * height * 4);
    for (unsigned i = 0; i < width * height; ++i) {
        image[4 * i + 0] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][0], 0.f, 1.f)); // R
        image[4 * i + 1] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][1], 0.f, 1.f)); // G
        image[4 * i + 2] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][2], 0.f, 1.f)); // B
        image[4 * i + 3] = 255; // A (прозрачность — полностью непрозрачный)
    }

    // Сохранение в PNG
    unsigned error = lodepng::encode("out.png", image, width, height);

    if (error) {
        std::cout << "An error occurred while saving to png: " << lodepng_error_text(error) << std::endl;
    }
}

void RayTracer::saveAsPNG(std::vector<Vector4f> frame_buffer) const{
    // Массив RGBA (lodepng требует 4 канала)
    std::vector<unsigned char> image(width * height * 4);
    for (unsigned i = 0; i < width * height; ++i) {
        image[4 * i + 0] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][0], 0.f, 1.f)); // R
        image[4 * i + 1] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][1], 0.f, 1.f)); // G
        image[4 * i + 2] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][2], 0.f, 1.f)); // B
        image[4 * i + 3] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][3], 0.f, 1.f)); // A
    }

    // Сохранение в PNG
    unsigned error = lodepng::encode("out.png", image, width, height);

    if (error) {
        std::cout << "An error occurred while saving to png: " << lodepng_error_text(error) << std::endl;
    }
}