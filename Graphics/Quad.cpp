#include "Quad.h"

namespace JEngine {

    Quad::Quad(float x, float y, float width, float height)
    : _x(x), _y(y), _width(width), _height(height)
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
        _x += dx;
        _y += dy;
        
        float pos[] = {
            _x, _y,
            _x + _width, _y,
            _x + _width, _y + _height,
            _x, _y + _height
        };
        
        _mesh->setPosition(pos);
    }

    void Quad::setColor(int r, int g, int b) {
        float rr = (float)r/255.0f;
        float gg = (float)g/255.0f;
        float bb = (float)b/255.0f;
        
        float color[] = {
            rr, gg, bb,
            rr, gg, bb,
            rr, gg, bb,
            rr, gg, bb
        };
        
        _mesh->setColor(color);
    }

    void Quad::render() {
        _mesh->render();
    }

}