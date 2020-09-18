#pragma once

#include <memory>

#include "Quad.h"
#include "TexturedMesh.h"

namespace JEngine {

    class TexturedQuad : public Quad
    {
    public:
        TexturedQuad(float x, float y, float width, float height, const std::string& path);
        virtual ~TexturedQuad();

        void linearInterp(bool state) {
            dynamic_cast<TexturedMesh*>(_mesh)->linearInterp(state);
        }
        
    protected:
        void setUV(float* uv);

        int getImageWidth() const;
        int getImageHeight() const;
    };

}