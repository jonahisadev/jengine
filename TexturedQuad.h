#pragma once

#include "Quad.h"
#include "TexturedMesh.h"

namespace JEngine {

    class TexturedQuad : public Quad {
    public:
        TexturedQuad(float x, float y, float width, float height, const char* path);
        virtual ~TexturedQuad();
    };

}