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
        Vector3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

        T distance(const Vector3& other) const;
        static T distance(const Vector3& a, const Vector3& b);

        const Vector3& operator+(const Vector3& other);
        const Vector3& operator+=(const Vector3& other);

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

}