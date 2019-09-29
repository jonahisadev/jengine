#pragma once

#include "TexturedQuad.h"

namespace JEngine {

    class Spritesheet : public TexturedQuad {
    private:
        float _grid_size;
        Vector2f _grid_pos;
        
    public:
        Spritesheet(float x, float y, float width, float height, const char* path, float grid_size);
        virtual ~Spritesheet() {}
        
        void setGridPosition(float gx, float gy);
        void setGridPosition(Vector2f grid_pos);
        
        inline Vector2f getGridPosition() const { return _grid_pos; }
        inline float getGridSize() const { return _grid_size; }
        
    private:
        void updateUV();
    };

}