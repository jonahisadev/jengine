#pragma once

#include <memory>

namespace Jengine {

    class Vertex2 {
    private:
        float _x;
        float _y;

    public:
        Vertex2(float x, float y) : _x(x), _y(y) {}

        inline float x() const { return _x; }
        inline float y() const { return _y; }
    };

    typedef std::shared_ptr<Vertex2> Vertex2Ptr;

}