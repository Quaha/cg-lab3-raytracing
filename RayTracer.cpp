#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

#include "RayTracer.hpp"

#include "geometry.hpp"
#include "Material.hpp"
#include "Primitive.hpp"
#include "Light.hpp"

const Primitive& RayTracer::detectNearestObject(
    const Ray& ray,
    const std::vector<Primitive>& objects,
    const std::vector<Light>& lights) 
{
    float lowest_dist = std::numeric_limits<float>::max();
    size_t nearest_object_id = 0;
    for (size_t i = 0; i < objects.size(); ++i) {
        float current_dist = std::numeric_limits<float>::max();
        objects[i].figure->processRayIntersect(ray, current_dist);

        if (current_dist < lowest_dist) {
            nearest_object_id = i;
            lowest_dist = current_dist;
        }
    }
    return objects[nearest_object_id];
}

Vector3f RayTracer::getReflectDirection(const Vector3f& to_source, const Vector3f& normal) {
    return (normal * 2.0f * (to_source * normal) - to_source).normalize();
}

Vector3f RayTracer::castRay(
    const Ray& ray,
    const std::vector<Primitive>& objects,
    const std::vector<Light>& lights,
    size_t depth)
{
    float distance;
    const Primitive& nearest_object = detectNearestObject(ray, objects, lights);
    if (!nearest_object.figure->processRayIntersect(ray.start, ray.direction, distance)) {
        return background_color;
    }

    Vector3f point = ray.start + ray.direction * (distance - EPS);
    Vector3f normal = nearest_object.figure->getNormal(ray.start, ray.direction, distance);
    Vector3f view_dir = -ray.direction;

    Vector3f ambient = compMult(nearest_object.material.color, ambient_light);

    Vector3f diffuse(0.0f, 0.0f, 0.0f);
    Vector3f specular(0.0f, 0.0f, 0.0f);

    for (size_t i = 0; i < lights.size(); ++i) {

        Vector3f light_segment = point - lights[i].position;
        Vector3f to_light_dir = (lights[i].position - point).normalize();

        float distance = sqrtf(light_segment * light_segment);
        float intersect_dist = std::numeric_limits<float>::max();

        bool in_shadow = false;

        for (size_t j = 0; j < objects.size(); j++) {
            objects[j].figure->processRayIntersect(lights[i].position, -to_light_dir, intersect_dist);

            if (intersect_dist < distance) {
                in_shadow = true;
                break;
            }
        }

        if (in_shadow) continue;


        float diff_intensity = std::max(0.0f, to_light_dir * normal);
        
        Vector3f reflect_dir = getReflectDirection(to_light_dir, normal);
        float spec_intensity = std::pow(std::max(0.0f, reflect_dir * view_dir), nearest_object.material.specular_power);

        diffuse += lights[i].color * lights[i].intensity * diff_intensity;
        specular += lights[i].color * lights[i].intensity * spec_intensity;
    }

    Vector3f result_ambient = ambient;
    Vector3f result_diffuse = compMult(nearest_object.material.color, diffuse) * nearest_object.material.k_diffuse;
    Vector3f result_specular = specular * nearest_object.material.k_specular;

    if (nearest_object.material.reflector && depth < REFLECTION_DEPTH) {
        Vector3f reflect_dir = getReflectDirection(-ray.direction, normal);

        Vector3f reflect_color = castRay(Ray(point, reflect_dir), objects, lights, depth + 1);

        Vector3f result_color;
        result_color += (result_ambient + result_diffuse) * (1 - nearest_object.material.k_reflective);
        result_color += result_specular;
        result_color += reflect_color * nearest_object.material.k_reflective;
        
        return result_color;
    }

    return result_ambient + result_diffuse + result_specular;
}