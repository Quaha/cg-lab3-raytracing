#include "Material.hpp"

#include "geometry.hpp"

Material::Material(
	const Vector3f& color,
	float k_diffuse,
	size_t specular_power,
	float k_specular,
	bool reflector,
	float k_reflective,
	bool transparent,
	float k_transparency,
	float k_refraction)
{
	this->color = color;
	this->k_diffuse = k_diffuse;

	this->specular_power = specular_power;
	this->k_specular = k_specular;

	this->reflector = reflector;
	this->k_reflective = k_reflective;

	this->transparent = transparent;
	this->k_transparency = k_transparency;
	this->k_refraction = k_refraction;
}