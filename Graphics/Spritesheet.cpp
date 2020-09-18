#include "Spritesheet.h"

namespace JEngine {

    Spritesheet::Spritesheet(float x, float y, float width, float height, const std::string& path, float cell_size)
            : TexturedQuad(x, y, width, height, path), _cell_size(cell_size),
            _grid_size(float(getImageWidth()) / cell_size)
    {
        setGridPosition(0, 0);
    }

    void Spritesheet::setGridPosition(float gx, float gy)
    {
        _grid_pos = {gx, gy};
        updateUV();
    }

    void Spritesheet::setGridPosition(Vector2f grid_pos)
    {
        _grid_pos = grid_pos;
        updateUV();
    }

    void Spritesheet::updateUV()
    {
        Vector2f coords = {_grid_pos.x() * _cell_size, _grid_pos.y() * _cell_size};
        coords.normalize(float(getImageWidth()));

        float uv[] = {
                coords.u(), coords.v(),
                coords.u() + (_cell_size / (float) getImageWidth()), coords.v(),
                coords.u() + (_cell_size / (float) getImageWidth()),
                coords.v() + (_cell_size / (float) getImageHeight()),
                coords.u(), coords.v() + (_cell_size / (float) getImageHeight())
        };

        setUV(uv);
    }

    void Spritesheet::next()
    {
        _grid_pos.translate(1, 0);
        if (_grid_pos.x() == _grid_size) {
            _grid_pos.translate(-_grid_size, 1);
            if (_grid_pos.y() == _grid_size)
                _grid_pos = {0, 0};
        }
        updateUV();
    }

    void Spritesheet::prev()
    {
        _grid_pos.translate(-1, 0);
        if (_grid_pos.x() == -1) {
            _grid_pos.translate(_grid_size, -1);
            if (_grid_pos.y() == -1)
                _grid_pos = {_grid_size - 1, _grid_size - 1};
        }
        updateUV();
    }

}