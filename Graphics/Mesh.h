#pragma once

#include "OpenGL.h"
#include "Shaders/Shader.h"
#include "../Math/Vector.h"
#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace JEngine {

    class Mesh
    {
    protected:
        int _vertex_count;
        int _list_count;
        
        GLuint _vao, _vbo, _ebo;
        Shader* _shader;
        Vector3f _color;
        glm::mat4 _model;
        float _angle = 0.0f;
        
    public:
        Mesh(float *buffer, const Vector3f& color, int *els, int vCount, int lCount);
        virtual ~Mesh();
        
        void setPosition(const Vector2f& pos);
        void setColor(const Vector3f& color);
        void setRotation(float angle);

        void updateBufferData(float* data);

        void translate(const Vector2f& pos);
        void rotate(float dr);

        virtual void render(Matrix4f screen);
    };
    
}