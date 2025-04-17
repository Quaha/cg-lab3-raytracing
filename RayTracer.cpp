#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <format>
#include <limits>

#include "RayTracer.hpp"

#include "geometry.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Primitive.hpp"
#include "PNGsaver.hpp"
#include "Light.hpp"

void RayTracer::initObjects() {
    
    Material red_surface(Vector3f(0.8f, 0.0f, 0.0f), 1.0f, 200.0f, 1.5f, true, 0.1f);
    Material green_surface(Vector3f(0.2f, 0.7f, 0.3f), 1.0f, 5.0f, 0.1f, false, 0.0f);
    Material blue_surface(Vector3f(0.1f, 0.1f, 0.8f), 1.0f, 60.0f, 0.2f, false, 0.0f);
    Material reflector_surface(Vector3f(0.0f, 0.0f, 0.0f), 0.0f, 500.0f, 5.0f, true, 0.85f);

    this->objects.push_back(Primitive(Vector3f(-0.5f, 0.2f, 0.3f), 0.33f, red_surface));
    this->objects.push_back(Primitive(Vector3f(0.3f, 0.2f, 0.0f), 0.25f, blue_surface));
    this->objects.push_back(Primitive(Vector3f(0.0f, 0.0f, -0.5f), 0.5f, green_surface));

    this->objects.push_back(Primitive(Vector3f(1.2f, -0.1f, -0.36f), 0.4f, reflector_surface));
    this->objects.push_back(Primitive(Vector3f(-1.3f, -0.3f, 0.27f), 0.34f, reflector_surface));
}

void RayTracer::initCameras() {

    Camera camera1(Vector3f(0.0f, 0.0f, 2.0f),
                   Vector3f(0.0f, 0.0f, 0.0f),
                   degreesToRadians(60.0f));

    this->cameras.push_back(camera1);

    Camera camera2(Vector3f(-1.0f, -3.0f, -1.0f),
                   Vector3f(0.0f, 0.0f, 0.0f),
                   degreesToRadians(60.0f));

    this->cameras.push_back(camera2);

    Camera camera3(Vector3f(-1.0f, 3.0f, -2.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        degreesToRadians(60.0f));

    this->cameras.push_back(camera3);
}

void RayTracer::initLights() {
    this->lights.push_back(Light(Vector3f(2.0f, -2.2f, 2.0f), 0.8f, Vector3f(1.0f, 1.0f, 1.0f)));
    this->lights.push_back(Light(Vector3f(0.0f, 3.0f, 0.0f), 0.8f, Vector3f(1.0f, 0.1f, 0.1f)));
    this->lights.push_back(Light(Vector3f(-2.0f, 0.0f, 2.0f), 0.8f, Vector3f(1.0f, 1.0f, 1.0f)));
}

RayTracer::RayTracer(unsigned int width,
                     unsigned int height): width(width), height(height) {

    initCameras();
    initLights();
    initObjects();
}

Primitive& RayTracer::detectNearestObject(const Ray& ray) {
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

Vector3f reflect(const Vector3f& to_source, const Vector3f& normal) {
    return (normal * 2.0f * (to_source * normal) - to_source).normalize();
}

Vector3f RayTracer::castRay(const Ray& ray, size_t depth = 0) {

    float distance;
    const Primitive& nearest_object = detectNearestObject(ray);
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
        
        Vector3f reflect_dir = reflect(to_light_dir, normal);
        float spec_intensity = std::pow(std::max(0.0f, reflect_dir * view_dir), nearest_object.material.specular_power);

        diffuse += lights[i].color * lights[i].intensity * diff_intensity;
        specular += lights[i].color * lights[i].intensity * spec_intensity;
    }

    Vector3f result_ambient = ambient;
    Vector3f result_diffuse = compMult(nearest_object.material.color, diffuse) * nearest_object.material.k_diffuse;
    Vector3f result_specular = specular * nearest_object.material.k_specular;


    if (nearest_object.material.reflector && depth < REFLECTION_DEPTH) {
        Vector3f reflect_dir = reflect(-ray.direction, normal);

        Vector3f reflect_color = castRay(Ray(point, reflect_dir), depth + 1);

        Vector3f result_color;
        result_color += (result_ambient + result_diffuse) * (1 - nearest_object.material.k_reflective);
        result_color += result_specular;
        result_color += reflect_color * nearest_object.material.k_reflective;
        
        return result_color;
    }

    return result_ambient + result_diffuse + result_specular;
}


void RayTracer::render() {

    std::vector<Vector3f> frame_buffer(width * height);

    for (size_t k = 0; k < cameras.size(); ++k) {
        const Camera& camera = cameras[k];
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {

                /*
                * 1. xp = (j + 0.5) / width: j in [0, width] -> [0, 1]
                * 2. (2 * xp - 1): xp in [0, 1] -> xp in [-1, 1]
                * 3. xp *  tan(camera.getFOV() / 2): Conversion depending on FOV
                * 4. width / heigh: Correction due to differences in the sides
                */

                float scale = tan(camera.getFOV() / 2.0f);
                float screen_aspect_ratio = width / (float)height;

                float x = (2 * (j + 0.5f) / (float)width - 1) * scale * screen_aspect_ratio;
                float y = (2 * (i + 0.5f) / (float)height - 1) * scale;

                Vector3f direction = (camera.getRight() * x +
                                      camera.getUp() * y +
                                      camera.getForward()).normalize();

                Ray ray(camera.getPosition(), direction);
                frame_buffer[j + i * width] = castRay(ray);
            }
        }
        PNGsaver::saveAsPNG(std::format("photo{}.png", k), frame_buffer, width, height);
    }
}