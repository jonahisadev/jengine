#include "TextField.h"
#include "../Display.h"

namespace JEngine {

    TextField::TextField(float x, float y, const std::string& font)
    : _view(x, y, 200, 40, 3)
    {
        _font = new Font(font.c_str(), 16);
        _text_pos = {x + (3*2), y + (40 - (3 * 2))};
    }

    TextField::~TextField() {
        delete _font;
    }

    void TextField::render() {
        _view.border.render();
        _view.fill.render();
        _font->render(_text_pos.x(), _text_pos.y(), _text, {0, 0, 0});
    }

    void TextField::install(Display &display) {
        display.installUI(this);
    }

}