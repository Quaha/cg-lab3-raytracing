#include <vector>
#include <iostream>
#include <algorithm>

#include "geometry.hpp"

#include "lodepng.h"

void render() {
    const unsigned width = 1280;
    const unsigned height = 720;

    std::vector<Vector3f> framebuffer(width * height);

    for (size_t i = 0; i != height; ++i) {
        for (size_t j = 0; j != width; ++j) {
            framebuffer[j + i * width] = Vector3f((float)i / height, (float)j / width, (float)i * j);
        }
    }

    // Массив RGBA (lodepng требует 4 канала)
    std::vector<unsigned char> image(width * height * 4);
    for (unsigned i = 0; i < width * height; ++i) {
        image[4 * i + 0] = static_cast<unsigned char>(255 * clamp(framebuffer[i][0], 0.f, 1.f)); // R
        image[4 * i + 1] = static_cast<unsigned char>(255 * clamp(framebuffer[i][1], 0.f, 1.f)); // G
        image[4 * i + 2] = static_cast<unsigned char>(255 * clamp(framebuffer[i][2], 0.f, 1.f)); // B
        image[4 * i + 3] = 255; // A (прозрачность — полностью непрозрачный)
    }

    // Сохранение в PNG
    unsigned error = lodepng::encode("out.png", image, width, height);

    if (error) {
        std::cout << "An error occurred while saving to png: " << lodepng_error_text(error) << std::endl;
    }
}