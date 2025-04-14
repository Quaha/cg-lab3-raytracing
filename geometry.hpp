#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>

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

    // Приводит длину вектора к заданной
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
Vector<dimension, T> operator-(const Vector<dimension, T>& v) {
    return v * T(-1);
}

template <typename T> 
Vector<3, T> cross(Vector<3, T> v1, Vector<3, T> v2) {
    return Vector<3, T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template <typename T>
T scalar(Vector<3, T> v1, Vector<3, T> v2) {
    return T(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

template <size_t dimension, typename T> 
std::ostream& operator<<(std::ostream& out, const Vector<dimension, T>& v) {
    for (size_t i = 0; i != dimension; ++i) {
        out << v[i] << " ";
    }
    return out;
}

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