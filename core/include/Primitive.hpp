#pragma once

#include "geometry.hpp"
#include "Material.hpp"

struct Primitive {

	Material material;
	std::unique_ptr<Figure> figure;

	Primitive(const Vector3f& center, float radius, const Material& material);
	Primitive(const Vector3f& A, const Vector3f& B, const Vector3f& C, const Material& material);
};