#include <memory>

#include "Primitive.hpp"

#include "geometry.hpp"
#include "Material.hpp";

Primitive::Primitive(const Vector3f& center, float radius, const Material& material) {
	this->material = material;
	figure = std::make_unique<Sphere>(center, radius);
}