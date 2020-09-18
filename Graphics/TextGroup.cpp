#include "TextGroup.h"

namespace JEngine {

    TextGroup::TextGroup(Font& font, const Vector3f& color, float padding)
            : _font(font), _color(color), _padding(padding)
    {}

    TextGroup::~TextGroup()
    {}

    void TextGroup::add(const std::string& str)
    {
        _text.push_back(str);
    }

    void TextGroup::render(float x, float y)
    {
        float height = y;

        for (auto& str : _text) {
            height += _font.height(str);
            _font.render(x, height, str, _color);
            height += _padding;
        }
    }

    void TextGroup::reset()
    {
        _text.clear();
    }

}