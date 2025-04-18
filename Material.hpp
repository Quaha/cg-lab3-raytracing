#pragma once

#include "geometry.hpp"

struct Material {

	Vector3f color;
	float k_diffuse;

	float specular_power; // sharpness of glare
	float k_specular;

	bool reflector;
	float k_reflective;

	bool transparent;
	float k_transparency;
	float k_refraction;

	Material() = default;

	Material(
		const Vector3f& color,
		float k_diffuse,
		float specular_power,
		float k_specular,
		bool reflector,
		float k_reflective,
		bool transparent,
		float k_transparency,
		float k_refraction);
};