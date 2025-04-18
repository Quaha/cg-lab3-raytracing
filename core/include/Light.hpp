#pragma once

#include "geometry.hpp"

struct Light {

    Vector3f position;
    Vector3f color;
    float intensity;

    Light(const Vector3f& position, const float& intensity, const Vector3f& color) :
        position(position), intensity(intensity), color(color) {}
};