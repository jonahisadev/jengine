#include "Sprite.h"

namespace JEngine {

    Sprite::Sprite(Spritesheet& parent, float x, float y, float width, float height, Vector2i grid_pos)
        : Quad(x, y, width, height), _parent(parent), _grid_pos(grid_pos)
    {}

    Sprite::~Sprite()
    {}

    void Sprite::render(Matrix4f screen)
    {
        _parent.renderSubSprite(screen, *this);
    }

    void Sprite::setGridPosition(Vector2i grid_pos)
    {
        _grid_pos = grid_pos;
    }

}