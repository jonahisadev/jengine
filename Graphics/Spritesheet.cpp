#include "Spritesheet.h"

namespace JEngine {

    Spritesheet::Spritesheet(float x, float y, float width, float height, const char *path, float grid_size)
    : TexturedQuad(x, y, width, height, path), _grid_size(grid_size)
    {
        _grid_pos = {0, 0};
    }

    void Spritesheet::setGridPosition(float gx, float gy) {
        _grid_pos = {gx, gy};
        updateUV();
    }

    void Spritesheet::setGridPosition(Vector2f grid_pos) {
        _grid_pos = grid_pos;
        updateUV();
    }

    void Spritesheet::updateUV() {
        Vector2f coords = {_grid_pos.x() * _grid_size, _grid_pos.y() * _grid_size};
        coords.normalize(float(getImageWidth()));
        
        float uv[] = {
            coords.u(), coords.v(),
            coords.u() + (_grid_size / (float)getImageWidth()), coords.v(),
            coords.u() + (_grid_size / (float)getImageWidth()), coords.v() + (_grid_size / (float)getImageHeight()),
            coords.u(), coords.v() + (_grid_size / (float)getImageHeight())
        };
        
        setUV(uv);
    }

}