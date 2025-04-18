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

Vector3f RayTracer::getRefractDirection(const Vector3f& from_source, const Vector3f& normal, float out_k, float in_k) {
    float cosi = clamp(from_source * normal, -1.0f, 1.0f);
    float eta = out_k / in_k;

    float k = 1.0f - eta * eta * (1.0f - cosi * cosi);

    return (from_source * eta + normal * (eta * cosi - sqrtf(k))).normalize();
}

Vector3f RayTracer::castRay(
    const Ray& ray,
    const std::vector<Primitive>& objects,
    const std::vector<Light>& lights,
    size_t depth,
    float k_refraction)
{
    float distance;
    const Primitive& nearest_object = detectNearestObject(ray, objects, lights);
    if (!nearest_object.figure->processRayIntersect(ray.start, ray.direction, distance)) {
        return background_color;
    }

    Vector3f point_in = ray.start + ray.direction * (distance + EPS);
    Vector3f point_out = ray.start + ray.direction * (distance - EPS);
    Vector3f normal = nearest_object.figure->getNormal(ray.start, ray.direction, distance);
    Vector3f view_dir = -ray.direction; // to ray source

    Vector3f diffuse(0.0f, 0.0f, 0.0f);
    Vector3f specular(0.0f, 0.0f, 0.0f);

    for (size_t i = 0; i < lights.size(); ++i) {

        Vector3f light_segment = point_out - lights[i].position;
        Vector3f to_light_dir = (lights[i].position - point_out).normalize();

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

    Vector3f result_ambient = compMult(nearest_object.material.color, ambient_light);
    Vector3f result_diffuse = compMult(nearest_object.material.color, diffuse) * nearest_object.material.k_diffuse;
    Vector3f result_specular = specular * nearest_object.material.k_specular;

    Vector3f result_reflect(0.0f, 0.0f, 0.0f);
    if (nearest_object.material.reflector && depth < REFLECTION_DEPTH) {
        Vector3f reflect_dir = getReflectDirection(-ray.direction, normal);

        result_reflect = castRay(Ray(point_out, reflect_dir), objects, lights, depth + 1, k_refraction);
    }

    Vector3f result_transpar(0.0f, 0.0f, 0.0f);
    if (nearest_object.material.transparent && depth < REFLECTION_DEPTH) {

        float out_k = k_refraction;
        float in_k = nearest_object.material.k_refraction;

        Vector3f transpar_dir = getRefractDirection(ray.direction, normal, out_k, in_k);
        result_transpar = castRay(Ray(point_in, transpar_dir), objects, lights, depth + 1, nearest_object.material.k_refraction);
    }

    Vector3f result_color =
        (result_ambient + result_diffuse) *
        (1.0f - nearest_object.material.k_reflective - nearest_object.material.k_transparency) +
        result_specular +
        result_reflect * nearest_object.material.k_reflective +
        result_transpar * nearest_object.material.k_transparency;

    return result_color;
}