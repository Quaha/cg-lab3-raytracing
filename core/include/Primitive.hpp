#pragma once

#include <memory>

#include "geometry.hpp"
#include "Material.hpp"

struct Primitive {

	Material material;
	std::unique_ptr<Figure> figure;

	Primitive(const Vector3f& center, float radius, const Material& material);
};