#pragma once

#include "OpenGL.h"

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
        
    private:
        GLuint _buffers[BufferCount];
        int _vertex_count;
        int _list_count;
        
    public:
        Mesh(float* pos, float* color, int* els, int vCount, int lCount);
        virtual ~Mesh();
        
        void setPosition(float* pos);
        void setColor(float* color);
        
        void render();
    };
    
}