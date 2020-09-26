#include "Quad.h"

namespace JEngine {

    Quad::Quad(float x, float y, float width, float height)
        : _pos(x, y), _size(width, height), _color(1, 1, 1), _angle(0)
    {}

    Quad::~Quad()
    {}

    void Quad::translate(float dx, float dy)
    {
        _pos.translate(dx, dy);
        setPosition(_pos);
    }

    void Quad::translate(const Vector2f& vec)
    {
        translate(vec.x(), vec.y());
    }

    void Quad::rotate(float dr)
    {
        _angle += dr;
        setRotation(_angle);
    }

    void Quad::setPosition(float x, float y)
    {
        _pos = {x, y};
    }

    void Quad::setPosition(const Vector2f& pos)
    {
        _pos = pos;
    }

    void Quad::setRotation(float angle)
    {
        _angle = angle;
    }

    void Quad::setColor(int r, int g, int b)
    {
        _color.setR(r);
        _color.setG(g);
        _color.setB(b);
        _color.normalize(255);
    }

    void Quad::setColor(const Vector3i& rgb)
    {
        setColor(rgb.r(), rgb.g(), rgb.b());
    }

    void Quad::setColor(const Vector3f& rgb)
    {
        _color = rgb;
    }

    void Quad::setCenter(Vector2f center)
    {
        setPosition(center.x() - (width() / 2), center.y() - (height() / 2));
    }

    bool Quad::intersects(const Quad& other) const
    {
        return x() + width() >= other.x() && x() <= other.x() + other.width() &&
               y() + height() >= other.y() && y() <= other.y() + other.height();
    }

    bool Quad::intersects(const Vector2f& vec) const
    {
        return vec.x() >= x() && vec.x() <= x() + width() &&
               vec.y() >= y() && vec.y() <= y() + height();
    }

    bool Quad::intersects(const Quad& a, const Quad& b)
    {
        return a.intersects(b);
    }

    bool Quad::intersects(const Quad& quad, const Vector2f& vec)
    {
        return quad.intersects(vec);
    }

}