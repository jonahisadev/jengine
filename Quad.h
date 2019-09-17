#pragma once

#include "Mesh.h"

namespace JEngine {

    class Quad {
    protected:
        float _x, _y, _width, _height;
        MeshPtr _mesh;
        
    public:
        Quad(float x, float y, float width, float height);
        virtual ~Quad();
        
        void translate(float dx, float dy);
        void setColor(int r, int g, int b);
        
        void render();
    };

}