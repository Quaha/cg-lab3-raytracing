#include <vector>
#include <iostream>
#include <algorithm>

#include "RayTracer.hpp"

#include "geometry.hpp"

#include "lodepng.h"

Vector3f castRay(const Vector3f& orig, const Vector3f& dir, const Sphere& sphere) {
    float sphere_dist = std::numeric_limits<float>::max();
    if (!sphere.processRayIntersect(orig, dir, sphere_dist)) {
        return Vector3f(0.2, 0.7, 0.8); // background color
    }
    return Vector3f(0.4, 0.4, 0.3);
}

RayTracer::RayTracer(unsigned int width,
                     unsigned int height): width(width), height(height) {
    
    camera = Camera(Vector3f(0, 0, 0), Vector3f(0, 0, 0), degreesToRadians(45.0f));
}

void RayTracer::render() {

    std::vector<Vector3f> frame_buffer(width * height);

    Sphere sphere(0, 0, -3, 1.0f);

    for (size_t i = 0; i != height; ++i) {
        for (size_t j = 0; j != width; ++j) {
            float x = (2 * (j + 0.5) / (float)width - 1) * tan(camera.getFOV() / 2.0f) * width / (float)height;
            float y = -(2 * (i + 0.5) / (float)height - 1) * tan(camera.getFOV() / 2.0f);
            Vector3f dir = Vector3f(x, y, -1).normalize();
            frame_buffer[j + i * width] = castRay(camera.getPosition(), dir, sphere);
        }
    }

    saveAsPNG(frame_buffer);
}

void RayTracer::saveAsPNG(std::vector<Vector3f> frame_buffer) {
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

void RayTracer::saveAsPNG(std::vector<Vector4f> frame_buffer) {
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