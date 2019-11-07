#pragma once

#include <vector>

#include "Font.h"

namespace JEngine {

    class TextGroup {
    private:
        Font& _font;
        std::vector<std::string> _text;
        Vector3f _color;
        float _padding;
        
    public:
        TextGroup(Font& font, const Vector3f& color = {1, 1, 1}, float padding = 5);
        virtual ~TextGroup();
        
        void add(const std::string& str);
        void render(float x, float y);
        
        void reset();
    };

}