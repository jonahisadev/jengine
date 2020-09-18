#include "Quad.h"

namespace JEngine {

    Quad::Quad(float x, float y, float width, float height)
            : _pos(x, y), _size(width, height), _color(1, 1, 1)
    {
        float ox = (width / 2);
        float oy = (height / 2);
        float buffer[] = {
                -ox, -oy, 0, 0,
                ox, -oy, 0, 0,
                ox, oy, 0, 0,
                -ox, oy, 0, 0
        };

        Vector3f color = {1, 1, 1};

        int els[] = {
                0, 1, 2,
                0, 3, 2
        };

        _pos.translate(-ox, -oy);
        _angle = 0;
        _mesh = new Mesh(buffer, color, els, 4, 6);

        setPosition(_pos.x() + (width / 2), _pos.y() + (height / 2));
        setColor(_color);
    }

    Quad::~Quad()
    {
        delete _mesh;
    }

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
        _mesh->rotate(dr);
    }

    void Quad::setPosition(float x, float y)
    {
        _pos = {x, y};
        _mesh->setPosition({_pos.x() + width() / 2, _pos.y() + height() / 2});
    }

    void Quad::setPosition(const Vector2f& pos)
    {
        setPosition(pos.x(), pos.y());
    }

    void Quad::setAngle(float angle)
    {
        _angle = angle;
    }

    void Quad::setColor(int r, int g, int b)
    {
        _color.setR(r);
        _color.setG(g);
        _color.setB(b);
        _color.normalize(255);
        _mesh->setColor(_color);
    }

    void Quad::setColor(const Vector3i& rgb)
    {
        setColor(rgb.r(), rgb.g(), rgb.b());
    }

    void Quad::setColor(const Vector3f& rgb)
    {
        _color = rgb;
        _mesh->setColor(_color);
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

    void Quad::render(Matrix4f screen)
    {
        _mesh->render(screen);
    }

}