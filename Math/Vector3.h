#pragma once

#include <memory>
#include <cmath>

namespace JEngine {

    template <class T> class Vector3;

    template <class T>
    class Vector3 {
    public:
        typedef std::shared_ptr< Vector3<T> > Ptr;

    private:
        T _x;
        T _y;
        T _z;

    public:
        Vector3() = default;
        Vector3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

        T distance(const Vector3& other) const;
        static T distance(const Vector3& a, const Vector3& b);

        void translate(T dx, T dy, T dz);
        const Vector3<T>& normalize(T max);

        const Vector3& operator+(const Vector3& other);
        const Vector3& operator+=(const Vector3& other);
        Vector3& operator=(Vector3 other);

        inline void setX(T x) { _x = x; }
        inline void setY(T y) { _y = y; }
        inline void setZ(T z) { _z = z; }
        inline void setR(T r) { _x = r; }
        inline void setG(T g) { _y = g; }
        inline void setB(T b) { _z = b; }

        inline T x() const { return _x; }
        inline T y() const { return _y; }
        inline T z() const { return _z; }
        inline T r() const { return _x; }
        inline T g() const { return _y; }
        inline T b() const { return _z; }
    };

    typedef Vector3<int> Vector3i;
    typedef Vector3<float> Vector3f;

    template<class T>
    T Vector3<T>::distance(const Vector3 &other) const {
        T x = other.x() - _x;
        T y = other.y() - _y;
        T z = other.z() - _z;
        return (T) sqrt((x * x) + (y * y) + (z * z));
    }

    template<class T>
    T Vector3<T>::distance(const Vector3 &a, const Vector3 &b) {
        return a.distance(b);
    }

    template<class T>
    void Vector3<T>::translate(T dx, T dy, T dz) {
        _x += dx;
        _y += dy;
        _z += dz;
    }

    template<class T>
    const Vector3<T>& Vector3<T>::normalize(T max) {
        setX(_x / max);
        setY(_y / max);
        setZ(_z / max);
        return *this;
    }

    template<class T>
    const Vector3<T>& Vector3<T>::operator+(const Vector3 &other) {
        _x += other.x();
        _y += other.y();
        _z += other.z();
        return *this;
    }

    template<class T>
    const Vector3<T>& Vector3<T>::operator+=(const Vector3 &other) {
        return *this + other;
    }

    template<class T>
    Vector3<T>& Vector3<T>::operator=(Vector3 other) {
        _x = other.x();
        _y = other.y();
        _z = other.z();
        return *this;
    }

}
