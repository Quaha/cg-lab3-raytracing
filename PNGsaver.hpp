#pragma once

#include <vector>
#include <string>

#include "geometry.hpp"

class PNGsaver {
public:

    static void saveAsPNG(const std::string& name,
                          std::vector<Vector3f> frame_buffer,
                          unsigned int width,
                          unsigned int height);

    static void saveAsPNG(const std::string& name,
                          std::vector<Vector4f> frame_buffer,
                          unsigned int width,
                          unsigned int height);
};