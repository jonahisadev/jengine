#pragma once

#include "Mesh.h"
#include <SOIL/SOIL.h>

#include <iostream>

namespace JEngine {

    class TexturedMesh : public Mesh {
    public:
        TexturedMesh(float* pos, float* color, int* els, int vCount, int lCount, const char* path);
        virtual ~TexturedMesh();
    };
    
}