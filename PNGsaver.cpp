#include <vector>
#include <string>

#include "lodepng.h"

#include "PNGsaver.hpp"

#include "geometry.hpp"

void PNGsaver::saveAsPNG(const std::string& name,
                         std::vector<Vector3f> frame_buffer,
                         unsigned int width,
                         unsigned int height)
{
    // ������ RGBA (lodepng ������� 4 ������)
    std::vector<unsigned char> image(width * height * 4);
    for (unsigned i = 0; i < width * height; ++i) {
        image[4 * i + 0] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][0], 0.0f, 1.0f)); // R
        image[4 * i + 1] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][1], 0.0f, 1.0f)); // G
        image[4 * i + 2] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][2], 0.0f, 1.0f)); // B
        image[4 * i + 3] = 255; // A (������������ � ��������� ������������)
    }

    // ���������� � PNG
    unsigned error = lodepng::encode(name, image, width, height);

    if (error) {
        std::cout << "An error occurred while saving to png " << name << ": " << lodepng_error_text(error) << std::endl;
    }
}

void PNGsaver::saveAsPNG(const std::string& name,
                         std::vector<Vector4f> frame_buffer,
                         unsigned int width,
                         unsigned int height)
{
    // ������ RGBA (lodepng ������� 4 ������)
    std::vector<unsigned char> image(width * height * 4);
    for (unsigned i = 0; i < width * height; ++i) {
        image[4 * i + 0] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][0], 0.0f, 1.0f)); // R
        image[4 * i + 1] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][1], 0.0f, 1.0f)); // G
        image[4 * i + 2] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][2], 0.0f, 1.0f)); // B
        image[4 * i + 3] = static_cast<unsigned char>(255 * clamp(frame_buffer[i][3], 0.0f, 1.0f)); // A
    }

    // ���������� � PNG
    unsigned error = lodepng::encode(name, image, width, height);

    if (error) {
        std::cout << "An error occurred while saving to png " << name << ": " << lodepng_error_text(error) << std::endl;
    }
}