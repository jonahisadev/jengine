#pragma once

#include "OpenGL.h"
#include "Shaders/Shader.h"
#include "../Math/Vector.h"
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

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
        
    public:
//        Mesh(float* pos, float* color, int* els, int vCount, int lCount);
        Mesh();
        virtual ~Mesh();
        
        void setPosition(float* pos);
        void setColor(float* color);
        
        void render();
    };
    
    typedef std::shared_ptr<Mesh> MeshPtr;
    
}