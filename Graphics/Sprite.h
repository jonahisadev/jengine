#pragma once

#include "Spritesheet.h"
#include "Quad.h"

namespace JEngine {

    class Sprite : public Quad
    {
    private:
        Spritesheet& _parent;
        Vector2i _grid_pos;

        friend class Spritesheet;

    public:
        Sprite(Spritesheet& parent, float x, float y, float width, float height, Vector2i grid_pos);
        virtual ~Sprite();

        void render(Matrix4f screen) override;
        void setGridPosition(Vector2i grid_pos);
    };

}