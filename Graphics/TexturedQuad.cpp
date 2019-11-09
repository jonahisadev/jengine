#include "TexturedQuad.h"

namespace JEngine {

    TexturedQuad::TexturedQuad(float x, float y, float width, float height, const char *path) 
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
        
        _mesh.reset();
        _mesh = std::make_shared<TexturedMesh>(buffer, color, els, 4, 6, path);
        
        setPosition(_pos);
        setColor(_color);
    }

    TexturedQuad::~TexturedQuad() {
        _mesh.reset();
    }

    void TexturedQuad::setUV(float *uv) {
        auto mesh = dynamic_cast<TexturedMesh*>(_mesh.get());
        mesh->setUV(uv);
    }

    int TexturedQuad::getImageWidth() const {
        auto mesh = dynamic_cast<TexturedMesh*>(_mesh.get());
        return mesh->getImageWidth();
    }

    int TexturedQuad::getImageHeight() const {
        auto mesh = dynamic_cast<TexturedMesh*>(_mesh.get());
        return mesh->getImageHeight();
    }

}