#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>

// ==================== Constants ====================

constexpr float PI = 3.14159265f;
constexpr float EPS = 0.001f;

// ==================== Vectors ====================

template <size_t dimension, typename T>
struct Vector {
    T data[dimension];

    Vector() {
        for (size_t i = 0; i != dimension; ++i) {
            data[i] = T();
        }
    }

    T& operator[](const size_t i) {
        assert(i < dimension);
        return data[i];
    }

    const T& operator[](const size_t i) const {
        assert(i < dimension);
        return data[i];
    }
};

using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;
using Vector4f = Vector<4, float>;

using Vector2i = Vector<2, int>;
using Vector3i = Vector<3, int>;
using Vector4i = Vector<4, int>;

template <typename T> 
struct Vector<2, T> {
    T x, y;

    Vector() : x(T()), y(T()) {}
    Vector(T X, T Y) : x(X), y(Y) {}

    template <class U>
    Vector<2, T>(const Vector<2, U>& v) {
        x = static_cast<T>(v[0]);
        y = static_cast<T>(v[1]);
    }

    T& operator[](const size_t i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        }
        assert(false);
    }

    const T& operator[](const size_t i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        }
        assert(false);
    }
};


template <typename T>
struct Vector<3, T> {
    T x, y, z;

    Vector() : x(T()), y(T()), z(T()) {}
    Vector(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

    template <class U>
    Vector<3, T>(const Vector<3, U>& v) {
        x = static_cast<T>(v[0]);
        y = static_cast<T>(v[1]);
        z = static_cast<T>(v[2]);
    }

    T& operator[](const size_t i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        }
        assert(false);
    }

    const T& operator[](const size_t i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        }
        assert(false);
    }

    float getNorm() {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Brings the length of the vector to the needed length
    Vector<3, T>& normalize(T len = T(1)) {
        const T scale = len / getNorm();

        x *= scale;
        y *= scale;
        z *= scale;

        return *this;
    }
};


template <typename T>
struct Vector<4, T> {
    T x, y, z, w;

    Vector() : x(T()), y(T()), z(T()), w(T()) {}
    Vector(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}

    template <class U>
    Vector<4, T>(const Vector<4, U>& v) {
        x = static_cast<T>(v[0]);
        y = static_cast<T>(v[1]);
        z = static_cast<T>(v[2]);
        w = static_cast<T>(v[3]);
    }

    T& operator[](const size_t i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        }
        assert(false);
    }

    const T& operator[](const size_t i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        }
        assert(false);
    }
};

template<size_t dimension, typename T>
T operator*(const Vector<dimension, T>& v1, const Vector<dimension, T>& v2) {
    T result = T();
    for (size_t i = 0; i != dimension; ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

template<size_t dimension, typename T>
Vector<dimension, T> operator+(const Vector<dimension, T>& v1, const Vector<dimension, T>& v2) {
    Vector<dimension, T> result;
    for (size_t i = 0; i != dimension; ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

template<size_t dimension, typename T>
Vector<dimension, T>& operator+=(Vector<dimension, T>& v1, const Vector<dimension, T>& v2) {
    for (size_t i = 0; i != dimension; ++i) {
        v1[i] += v2[i];
    }
    return v1;
}

template<size_t dimension, typename T>
Vector<dimension, T> operator-(const Vector<dimension, T>& v1, const Vector<dimension, T>& v2) {
    Vector<dimension, T> result;
    for (size_t i = 0; i != dimension; ++i) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

template<size_t dimension, typename T, typename U>
Vector<dimension, T> operator*(const Vector<dimension, T>& v, const U& c) {
    Vector<dimension, T> result;
    for (size_t i = 0; i != dimension; ++i) {
        result[i] = v[i] * c;
    }
    return result;
}

template<size_t dimension, typename T>
Vector<dimension, T> compMult(const Vector<dimension, T>& v1, const Vector<dimension, T>& v2) {
    Vector<dimension, T> result;
    for (size_t i = 0; i != dimension; ++i) {
        result[i] = v1[i] * v2[i];
    }
    return result;
}

template<size_t dimension, typename T>
Vector<dimension, T> operator-(const Vector<dimension, T>& v) {
    return v * T(-1);
}

template <typename T> 
Vector<3, T> cross(Vector<3, T> v1, Vector<3, T> v2) {
    return Vector<3, T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template <size_t dimension, typename T> 
std::ostream& operator<<(std::ostream& out, const Vector<dimension, T>& v) {
    for (size_t i = 0; i != dimension; ++i) {
        out << v[i] << " ";
    }
    return out;
}

// ==================== Functions ====================

template<typename T> 
T clamp(T f1, T f2, T f3) {
    if (f1 < f2) {
        return f2;
    }
    if (f1 > f3) {
        return f3;
    }
    return f1;
}

inline float degreesToRadians(float degrees) {
    return degrees * PI / 180.0f;
}

inline float radiansToDegrees(float radians) {
    return radians * 180.0f / PI;
}

// ==================== Figures ====================

struct Ray {

    Vector3f start;
    Vector3f direction; // should be normalized

    Ray(const Vector3f& start, const Vector3f& direction) {
        this->start = start;
        this->direction = direction;

        this->direction.normalize();
    }
};

struct Figure {

    virtual bool processRayIntersect(const Vector3f& start, const Vector3f& direction, float& intersect_dist) const = 0;

    bool processRayIntersect(const Ray& ray, float& intersect_dist) const {
        return processRayIntersect(ray.start, ray.direction, intersect_dist);
    }

    virtual Vector3f getNormal(const Vector3f& start, const Vector3f& direction, float intersect_dist) const = 0;

    virtual ~Figure() = default;

};

struct Sphere : Figure {

    Vector3f center;
    float radius;

    Sphere(const Vector3f& center, float radius) : center(center), radius(radius) {}
    Sphere(float x, float y, float z, float radius): radius(radius) {
        center = Vector3f(x, y, z);
    }

    bool processRayIntersect(const Vector3f& start, 
                             const Vector3f& direction,
                             float& intersect_dist) const override { 

        /* These equations could be derived from this system:
        *   
        *   / (v - center, v - center) = radius ^ 2
        *  <| 
        *   \ b = start + direction * t, t in R
        */   

        Vector3f L = start - center;

        float a = 1.0f; // because direction is normilized
        float b = 2.0f * (L * direction);
        float c = L * L - radius * radius;

        float D2 = b * b - 4.0f * c;

        if (D2 < 0) {
            return false;
        }

        float D = sqrtf(D2);

        float t1 = (-b - D) / 2.0f;
        float t2 = (-b + D) / 2.0f;

        if (t1 >= 0.0f) {
            intersect_dist = t1;
            return true;
        }
        else if (t2 >= 0.0f) {
            intersect_dist = t2;
            return true;
        }
        else {
            return false;
        }
    }

    Vector3f getNormal(const Vector3f& start,
                       const Vector3f& direction,
                       float intersect_dist) const override {
        Vector3f point = start + direction * intersect_dist;
        return (point - this->center).normalize();
    }
};