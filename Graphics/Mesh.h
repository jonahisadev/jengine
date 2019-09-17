#pragma once

#include "OpenGL.h"
#include <memory>

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
        
    public:
        Mesh(float* pos, float* color, int* els, int vCount, int lCount);
        virtual ~Mesh();
        
        void setPosition(float* pos);
        void setColor(float* color);
        
        void render();
    };
    
    typedef std::shared_ptr<Mesh> MeshPtr;
    
}