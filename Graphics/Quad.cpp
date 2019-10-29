#include "Quad.h"

namespace JEngine {

    Quad::Quad(float x, float y, float width, float height)
    : _pos(x, y), _size(width, height), _color(1, 1, 1)
    {
        float pos[] = {
            x, y,
            x + width, y,
            x + width, y + height,
            x, y + height
        };
        
        Vector3f color = {1, 1, 1};
        
        int els[] = {
            0, 1, 2,
            0, 3, 2
        };
        
        _angle = 0;
        _mesh = std::make_shared<Mesh>(pos, color, els, 4, 6);
    }

    Quad::~Quad() {
        _mesh.reset();
    }

    void Quad::translate(float dx, float dy) {
        _pos.translate(dx, dy);
        
        float pos[] = {
            _pos.x(), _pos.y(),
            _pos.x() + _size.x(), _pos.y(),
            _pos.x() + _size.x(), _pos.y() + _size.y(),
            _pos.x(), _pos.y() + _size.y()
        };
        
        _mesh->setPosition(pos);
    }

    void Quad::translate(const Vector2f &vec) {
        translate(vec.x(), vec.y());
    }

    void Quad::rotate(float dr) {
        _angle += dr;
        _mesh->rotate(dr);
    }

    void Quad::setPosition(float x, float y) {
        _pos.setX(x);
        _pos.setY(y);
        translate(0, 0);
    }

    void Quad::setPosition(const Vector2f &pos) {
        _pos = pos;
        translate(0, 0);
    }

    void Quad::setAngle(float angle) {
        _angle = angle;
    }

    void Quad::setColor(int r, int g, int b) {
        _color.setR(r);
        _color.setG(g);
        _color.setB(b);
        _color.normalize(255);
        _mesh->setColor(_color);
    }

    void Quad::setColor(const Vector3i &rgb) {
        setColor(rgb.r(), rgb.g(), rgb.b());
    }

    void Quad::setCenter(Vector2f center) {
        setPosition(center.x() - (width() / 2), center.y() - (height() / 2));
    }

    bool Quad::intersects(const Quad &other) const {
        return x() + width() >= other.x() && x() <= other.x() + other.width() &&
               y() + height() >= other.y() && y() <= other.y() + other.height();
    }

    bool Quad::intersects(const Vector2f &vec) const {
        return vec.x() >= x() && vec.x() <= x() + width() &&
               vec.y() >= y() && vec.y() <= y() + height();
    }

    bool Quad::intersects(const Quad &a, const Quad &b) {
        return a.intersects(b);
    }

    bool Quad::intersects(const Quad &quad, const Vector2f &vec) {
        return quad.intersects(vec);
    }

    void Quad::render(Matrix4f screen) {
//        glPushMatrix();
//        
//        glTranslatef(_pos.x() + (_size.x() / 2), _pos.y() + (_size.y() / 2), 0);
//        glRotatef(_angle, 0, 0, 1);
//        glTranslatef(-(_pos.x() + (_size.x() / 2)), -(_pos.y() + (_size.y() / 2)), 0);
        
        _mesh->render(screen);
        
//        glPopMatrix();
    }

}