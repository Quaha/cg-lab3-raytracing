#pragma once

#include <vector>

#include "geometry.hpp"
#include "Primitive.hpp"
#include "Light.hpp"

struct RayTracer {

	inline static Vector3f ambient_light = Vector3f(0.1f, 0.1f, 0.1f);
	inline static Vector3f background_color = Vector3f(0.2f, 0.7f, 0.8f);

	inline static size_t REFLECTION_DEPTH = 10;

	static const Primitive& detectNearestObject(const Ray& ray,
												const std::vector<Primitive>& objects,
												const std::vector<Light>& lights);

	static Vector3f getReflectDirection(const Vector3f& to_source, const Vector3f& normal);

	static Vector3f castRay(const Ray& ray,
							const std::vector<Primitive>& objects,
							const std::vector<Light>& lights,
							size_t depth = 0);
};