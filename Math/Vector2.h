#pragma once

#include <memory>
#include <cmath>

namespace JEngine {

    template <class T> class Vector2;

    template <class T>
    class Vector2
    {
    public:
        typedef std::shared_ptr< Vector2<T> > Ptr;

    private:
        T _x;
        T _y;

    public:
        Vector2() = default;
        Vector2(T x, T y) : _x(x), _y(y) {}

        T distance(const Vector2& other) const;
        static T distance(const Vector2& a, const Vector2& b);

        inline void translate(T dx, T dy);
        inline void translate(const Vector2<T>& vec);
        const Vector2<T>& normalize(T max);

        const Vector2& operator+(const Vector2& other);
        const Vector2& operator+=(const Vector2& other);
        const Vector2& operator-(const Vector2& other);
        const Vector2& operator-=(const Vector2& other);
        const Vector2& operator*(const Vector2& other);
        const Vector2& operator*=(const Vector2& other);
        const Vector2& operator*(T scalar);
        const Vector2& operator*=(T scalar);
        Vector2& operator=(Vector2 other);
        bool operator==(const Vector2& other);

        inline void setX(T x) { _x = x; }
        inline void setY(T y) { _y = y; }
        inline void setU(T u) { setX(u); }
        inline void setV(T v) { setY(v); }

        inline T x() const { return _x; }
        inline T y() const { return _y; }
        inline T u() const { return _x; }
        inline T v() const { return _y; }
    };

    typedef Vector2<int> Vector2i;
    typedef Vector2<float> Vector2f;

    template<class T>
    T Vector2<T>::distance(const Vector2 &other) const
    {
        T x = other.x() - _x;
        T y = other.y() - _y;
        return (T) sqrt((x * x) + (y * y));
    }

    template<class T>
    T Vector2<T>::distance(const Vector2 &a, const Vector2 &b)
    {
        return a.distance(b);
    }

    template<class T>
    void Vector2<T>::translate(T dx, T dy)
    {
        _x += dx;
        _y += dy;
    }

    template<class T>
    void Vector2<T>::translate(const Vector2<T> &vec)
    {
        translate(vec.x(), vec.y());
    }

    template<class T>
    const Vector2<T>& Vector2<T>::normalize(T max)
    {
        setX(_x / max);
        setY(_y / max);
        return *this;
    }

    template<class T>
    const Vector2<T>& Vector2<T>::operator+(const Vector2 &other)
    {
        _x += other.x();
        _y += other.y();
        return *this;
    }

    template<class T>
    const Vector2<T>& Vector2<T>::operator+=(const Vector2 &other)
    {
        return *this + other;
    }

    template<class T>
    const Vector2<T>& Vector2<T>::operator-(const Vector2 &other)
    {
        _x -= other.x();
        _y -= other.y();
        return *this;
    }

    template<class T>
    const Vector2<T>& Vector2<T>::operator-=(const Vector2 &other)
    {
        return *this - other;
    }

    template<class T>
    const Vector2<T>& Vector2<T>::operator*(const Vector2 &other)
    {
        _x *= other.x();
        _y *= other.y();
        return *this;
    }

    template<class T>
    const Vector2<T>& Vector2<T>::operator*=(const Vector2 &other)
    {
        return *this * other;
    }

    template<class T>
    const Vector2<T>& Vector2<T>::operator*(T scalar)
    {
        _x *= scalar;
        _y *= scalar;
        return *this;
    }

    template<class T>
    const Vector2<T>& Vector2<T>::operator*=(T scalar)
    {
        return *this * scalar;
    }

    template<class T>
    Vector2<T>& Vector2<T>::operator=(Vector2 other)
    {
        _x = other.x();
        _y = other.y();
        return *this;
    }

    template<class T>
    bool Vector2<T>::operator==(const Vector2& other)
    {
        return (_x == other.x() && _y == other.y());
    }
}
