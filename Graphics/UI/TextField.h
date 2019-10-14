#pragma once

#include "../Font.h"
#include "../Quad.h"

namespace JEngine {

    class Display;

    class TextField {
    private:
        struct View {
            Quad fill;
            Quad border;

            View(float x, float y, float width, float height, float pad)
            : fill(x + pad, y + pad, width - pad*2, height - pad*2), border(x, y, width, height)
            {
                fill.setColor(256, 256, 256);
                border.setColor(0, 0, 0);
            }
        } _view;

        Vector2f _text_pos;
        Font* _font;
        std::string _text;

        bool _focus = true;

    public:
        TextField(float x, float y, const std::string& font);
        ~TextField();

        void install(Display& display);
        void render();

        inline void append(char c) { _text += c; }
        inline void backspace() { _text.pop_back(); }

        inline bool focus() const { return _focus; }
    };

}