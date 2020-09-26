#include "BasicQuad.h"

namespace JEngine {

    BasicQuad::BasicQuad(float x, float y, float width, float height)
            : Quad(x, y, width, height)
    {
        float ox = (width / 2);
        float oy = (height / 2);
        float buffer[] = {
                -ox, -oy, 0, 0,
                ox, -oy, 0, 0,
                ox, oy, 0, 0,
                -ox, oy, 0, 0
        };

        int els[] = {
                0, 1, 2,
                0, 3, 2
        };

        _pos.translate(-ox, -oy);
        _angle = 0;
        _mesh = new Mesh(buffer, _color, els, 4, 6);

        setPosition(_pos.x() + (width / 2), _pos.y() + (height / 2));
        setColor(_color);
    }

    BasicQuad::~BasicQuad()
    {
        delete _mesh;
    }

    void BasicQuad::translate(float dx, float dy)
    {
        Quad::translate(dx, dy);
        setPosition(_pos);
    }

    void BasicQuad::translate(const Vector2f& vec)
    {
        Quad::translate(vec);
        setPosition(_pos);
    }

    void BasicQuad::rotate(float dr)
    {
        Quad::rotate(dr);
        setRotation(_angle);
    }

    void BasicQuad::setPosition(float x, float y)
    {
        Quad::setPosition(x, y);
        _mesh->setPosition({_pos.x() + width() / 2, _pos.y() + height() / 2});
    }

    void BasicQuad::setPosition(const Vector2f& pos)
    {
        Quad::setPosition(pos);
        _mesh->setPosition({_pos.x() + width() / 2, _pos.y() + height() / 2});
    }

    void BasicQuad::setSize(float width, float height)
    {
        Quad::setSize(width, height);

        float ox = (width / 2);
        float oy = (height / 2);
        float buffer[] = {
            -ox, -oy, 0, 0,
             ox, -oy, 0, 0,
             ox,  oy, 0, 0,
            -ox,  oy, 0, 0
        };
        _mesh->updateBufferData(buffer);
    }

    void BasicQuad::setSize(Vector2f size)
    {
        Quad::setSize(size);
        setSize(size.x(), size.y());
    }

    void BasicQuad::setRotation(float angle)
    {
        Quad::setRotation(angle);
        _mesh->setRotation(_angle);
    }

    void BasicQuad::setColor(int r, int g, int b)
    {
        Quad::setColor(r, g, b);
        _mesh->setColor(_color);
    }

    void BasicQuad::setColor(const Vector3i& rgb)
    {
        Quad::setColor(rgb);
        _mesh->setColor(_color);
    }

    void BasicQuad::setColor(const Vector3f& rgb)
    {
        Quad::setColor(rgb);
        _mesh->setColor(_color);
    }

    void BasicQuad::render(Matrix4f screen)
    {
        _mesh->render(screen);
    }

}