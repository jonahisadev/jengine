#pragma once

#include "Mesh.h"
#include <SOIL/SOIL.h>

#include <iostream>
#include <memory>

namespace JEngine {

    class TexturedMesh : public Mesh {
    protected:
        int _img_width;
        int _img_height;
        
    public:
        TexturedMesh(float* pos, float* color, int* els, int vCount, int lCount, const char* path);
        virtual ~TexturedMesh();
        
        void setUV(float* uv);
        void linearInterp(bool state);
        
        inline int getImageWidth() const { return _img_width; }
        inline int getImageHeight() const { return _img_height; }
    };
    
    typedef std::shared_ptr<TexturedMesh> TexturedMeshPtr;
    
}