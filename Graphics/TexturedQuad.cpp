#include "TexturedQuad.h"

namespace JEngine {

    TexturedQuad::TexturedQuad(float x, float y, float width, float height, const std::string& path)
            : Quad(x, y, width, height)
    {
        float ox = (width / 2);
        float oy = (height / 2);
        float buffer[] = {
                -ox, -oy, 0, 0,
                ox, -oy, 1, 0,
                ox, oy, 1, 1,
                -ox, oy, 0, 1
        };

        Vector3f color = {1, 1, 1};

        int els[] = {
                0, 1, 2,
                0, 3, 2
        };

        _angle = 0;
        _mesh = new TexturedMesh(buffer, _color, els, 4, 6, path);

        setPosition(_pos);
        setColor(_color);
    }

    TexturedQuad::~TexturedQuad()
    {
    }

    void TexturedQuad::translate(float dx, float dy)
    {
        Quad::translate(dx, dy);
        setPosition(_pos);
    }

    void TexturedQuad::translate(const Vector2f& vec)
    {
        Quad::translate(vec);
        setPosition(_pos);
    }

    void TexturedQuad::rotate(float dr)
    {
        Quad::rotate(dr);
        setRotation(_angle);
    }

    void TexturedQuad::setPosition(float x, float y)
    {
        Quad::setPosition(x, y);
        _mesh->setPosition({_pos.x() + width() / 2, _pos.y() + height() / 2});
    }

    void TexturedQuad::setPosition(const Vector2f& pos)
    {
        Quad::setPosition(pos);
        _mesh->setPosition({_pos.x() + width() / 2, _pos.y() + height() / 2});
    }

    void TexturedQuad::setSize(float width, float height)
    {
        if (_size == Vector2f{width, height})
            return;

        Quad::setSize(width, height);

        float ox = (width / 2);
        float oy = (height / 2);
        float buffer[] = {
            -ox, -oy, 0, 0,
             ox, -oy, 1, 0,
             ox,  oy, 1, 1,
            -ox,  oy, 0, 1
        };
        _mesh->updateBufferData(buffer);
    }

    void TexturedQuad::setSize(Vector2f size)
    {
        Quad::setSize(size);
        setSize(size.x(), size.y());
    }

    void TexturedQuad::setRotation(float angle)
    {
        Quad::setRotation(angle);
        _mesh->setRotation(_angle);
    }

    void TexturedQuad::setColor(int r, int g, int b)
    {
        Quad::setColor(r, g, b);
        _mesh->setColor(_color);
    }

    void TexturedQuad::setColor(const Vector3i& rgb)
    {
        Quad::setColor(rgb);
        _mesh->setColor(_color);
    }

    void TexturedQuad::setColor(const Vector3f& rgb)
    {
        Quad::setColor(rgb);
        _mesh->setColor(_color);
    }

    void TexturedQuad::setUV(float* uv)
    {
        _mesh->setUV(uv);
    }

    int TexturedQuad::getImageWidth() const
    {
        return _mesh->getImageWidth();
    }

    int TexturedQuad::getImageHeight() const
    {
        return _mesh->getImageHeight();
    }

    void TexturedQuad::render(Matrix4f screen)
    {
        _mesh->render(screen);
    }

}