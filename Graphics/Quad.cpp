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
        
        float color[] = {
            1, 1, 1,
            1, 1, 1,
            1, 1, 1,
            1, 1, 1
        };
        
        int els[] = {
            0, 1, 2,
            0, 3, 2
        };
        
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

    void Quad::setColor(int r, int g, int b) {
        _color.setR(r);
        _color.setG(g);
        _color.setB(b);
        _color.normalize(255);
        
        float color[] = {
            _color.r(), _color.g(), _color.b(),
            _color.r(), _color.g(), _color.b(),
            _color.r(), _color.g(), _color.b(),
            _color.r(), _color.g(), _color.b()
        };
        
        _mesh->setColor(color);
    }

    bool Quad::intersects(const Quad &other) const {
        return x() + width() >= other.x() && x() <= other.x() + other.width() &&
               y() + height() >= other.y() && y() <= other.y() + other.height();
    }

    bool Quad::intersects(const Quad &a, const Quad &b) {
        return a.intersects(b);
    }

    void Quad::render() {
        _mesh->render();
    }

}