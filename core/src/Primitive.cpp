#include <memory>

#include "Primitive.hpp"

#include "geometry.hpp"
#include "Material.hpp"

Primitive::Primitive(const Vector3f& center, float radius, const Material& material) {
	this->material = material;
	figure = std::make_unique<Sphere>(center, radius);
}

Primitive::Primitive(const Vector3f& A, const Vector3f& B, const Vector3f& C, const Material& material) {
	this->material = material;
	figure = std::make_unique<Triangle>(A, B, C);
}