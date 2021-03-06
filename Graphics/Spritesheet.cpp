#include "Spritesheet.h"
#include "Sprite.h"

#include <iostream>

namespace JEngine {

    Spritesheet::Spritesheet(float x, float y, float width, float height, const std::string& path, float cell_size)
            : TexturedQuad(x, y, width, height, path), _cell_size(cell_size),
            _grid_size(getImageWidth() / (int)cell_size), _current_cycle(nullptr)
    {
        setGridPosition(0, 0);
    }

    void Spritesheet::setGridPosition(int gx, int gy)
    {
        _grid_pos = {gx, gy};
        updateUV();
    }

    void Spritesheet::setGridPosition(Vector2i grid_pos)
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

        if (_current_cycle)
            validateCycle();

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

        if (_current_cycle)
            validateCycle();

        updateUV();
    }

    void Spritesheet::addCycle(const std::string& name, const Vector2i& start, const Vector2i& end)
    {
        int start_idx = start.y() * _grid_size + start.x();
        int end_idx = end.y() * _grid_size + end.x();
        _cycles[name] = new Cycle(name, start, start_idx, end_idx);
    }

    void Spritesheet::setActiveCycle(const std::string& name)
    {
        if (auto* cycle = _cycles[name]; cycle != _current_cycle)
            _current_cycle = cycle;
        setGridPosition(_current_cycle->start_pos);
    }

    void Spritesheet::clearActiveCycle()
    {
        _current_cycle = nullptr;
    }

    const std::string& Spritesheet::getActiveCycleName()
    {
        return _current_cycle->name;
    }

    Ref<Sprite> Spritesheet::createSprite(float x, float y, float width, float height, Vector2i grid_pos)
    {
        return make_ref<Sprite>(*this, x, y, width, height, grid_pos);
    }

    void Spritesheet::renderSubSprite(Matrix4f screen, Sprite& sprite)
    {
        // Set state
        setSize(sprite.width(), sprite.height());
        setPosition(sprite.x(), sprite.y());
        setRotation(sprite.angle());
        setColor(sprite.color());
        setGridPosition(sprite._grid_pos);

        // render
        render(screen);
    }

    void Spritesheet::validateCycle()
    {
        int grid_idx = _grid_pos.y() * _grid_size + _grid_pos.x();
        if (grid_idx < _current_cycle->start || grid_idx > _current_cycle->end)
            _grid_pos = _current_cycle->start_pos;
    }

}