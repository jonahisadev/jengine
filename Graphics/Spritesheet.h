#pragma once

#include "TexturedQuad.h"

namespace JEngine {

    class Spritesheet : public TexturedQuad {
    private:
        float _cell_size;
        float _grid_size;
        Vector2f _grid_pos;
        
    public:
        Spritesheet(float x, float y, float width, float height, const std::string& path, float cell_size);
        virtual ~Spritesheet() {}
        
        void setGridPosition(float gx, float gy);
        void setGridPosition(Vector2f grid_pos);
        void next();
        void prev();

        inline Vector2f getGridPosition() const { return _grid_pos; }
        inline float getCellSize() const { return _cell_size; }
        inline float getGridSize() const { return _grid_size; }
        
    private:
        void updateUV();
    };

}