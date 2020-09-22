#pragma once

#include <map>
#include <string>
#include "TexturedQuad.h"

namespace JEngine {

    class Spritesheet : public TexturedQuad
    {
    private:
        struct Cycle
        {
            std::string name;
            Vector2i start_pos;
            int start;
            int end;

            Cycle(const std::string& _name, const Vector2i _start_pos, int _start, int _end)
            {
                name = _name;
                start_pos = _start_pos;
                start = _start;
                end = _end;
            }
        };

        float _cell_size;
        int _grid_size;
        Vector2i _grid_pos;
        std::map<std::string, Cycle*> _cycles;
        Cycle* _current_cycle;

        void validateCycle();
        
    public:
        Spritesheet(float x, float y, float width, float height, const std::string& path, float cell_size);
        virtual ~Spritesheet() {}
        
        void setGridPosition(int gx, int gy);
        void setGridPosition(Vector2i grid_pos);
        void next();
        void prev();

        void addCycle(const std::string& name, const Vector2i& start, const Vector2i& end);
        void setActiveCycle(const std::string& name);
        void clearActiveCycle();
        const std::string& getActiveCycleName();

        inline Vector2i getGridPosition() const { return _grid_pos; }
        inline float getCellSize() const { return _cell_size; }
        inline int getGridSize() const { return _grid_size; }
        
    private:
        void updateUV();
    };

}