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
        
        GLuint _tex;
        
    public:
        TexturedMesh(float* pos, const Vector3f& color, int* els, int vCount, int lCount, const std::string& path);
        virtual ~TexturedMesh();
        
        void linearInterp(bool state);
        void render(Matrix4f screen) override;
        void setUV(const float* uv);
        
        inline int getImageWidth() const { return _img_width; }
        inline int getImageHeight() const { return _img_height; }
    };
    
}