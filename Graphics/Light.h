#pragma once

#include <glm/glm.hpp>
#include <SOIL/SOIL.h>
#include <vector>
#include <cmath>

#include "../Math/Vector.h"
#include "OpenGL.h"
#include "Shaders/Shader.h"
#include "TexturedMesh.h"
#include "Quad.h"

namespace JEngine {

    class Light {
    private:
        Vector2f _pos;
        float _diameter;
        float _radius;
        TexturedMeshPtr _mesh;
        
        std::vector<Vector2f> _points;
        
    public:
        Light(float x, float y, float diameter, const Vector3f& color);
        virtual ~Light();
        
        void prepare(std::vector<Quad>& items);
        
        void setPosition(float x, float y);
        void setCenter(float x, float y);
        
        Vector2f center() { return Vector2f(_pos.x(), _pos.y()); }
        
        void render(Matrix4f screen);
    };

}