#include "Material.hpp"

#include "geometry.hpp"

Material::Material(const Vector3f& color, float k_diffuse, float specular_power, float k_specular) {
	this->color = color;
	this->k_diffuse = k_diffuse;
	this->specular_power = specular_power;
	this->k_specular = k_specular;
}