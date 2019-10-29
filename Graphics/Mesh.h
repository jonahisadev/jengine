#pragma once

#include "OpenGL.h"
#include "Shaders/Shader.h"
#include "../Math/Vector.h"
#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace JEngine {

    class Mesh {
    public:
        enum BufferType {
            BufferPosition,
            BufferColor,
            BufferIndex,
            BufferCoords,
            BufferTexture,
            
            BufferCount
        };
        
    protected:
        GLuint _buffers[BufferCount];
        int _vertex_count;
        int _list_count;
        bool _textured = false;
        
        GLuint _vao, _vbo, _ebo;
        Shader _shader;
        Vector3f _color;
        glm::mat4 _model;
        float _angle = 0.0f;
        
    public:
        Mesh(float *pos, const Vector3f& color, int *els, int vCount, int lCount);
        virtual ~Mesh();
        
        void setPosition(float* pos);
        void setColor(const Vector3f& color);
        void rotate(float dr);
        
        void render(Matrix4f screen);
    };
    
    typedef std::shared_ptr<Mesh> MeshPtr;
    
}