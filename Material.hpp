#pragma once

#include "geometry.hpp"

struct Material {

	Vector3f color;
	float k_diffuse;

	float specular_power; // sharpness
	float k_specular;

	bool reflector;
	float k_reflective;

	Material() = default;
	Material(
		const Vector3f& color,
		float k_diffuse,
		float specular_power,
		float k_specular,
		bool reflector,
		float k_reflective);
};