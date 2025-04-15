#pragma once

#include "geometry.hpp"

struct Material {

	Vector3f color;

	Material() = default;
	Material(const Vector3f& color);
};