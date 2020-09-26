#pragma once

#include "Quad.h"
#include "Mesh.h"

namespace JEngine {

    class BasicQuad : public Quad
    {
    private:
        Mesh* _mesh;

    public:
        BasicQuad(float x, float y, float width, float height);
        virtual ~BasicQuad();

        void translate(float dx, float dy) override;
        void translate(const Vector2f& vec) override;
        void rotate(float dr) override;

        void setPosition(float x, float y) override;
        void setPosition(const Vector2f& pos) override;
        void setSize(float width, float height) override;
        void setSize(Vector2f size) override;
        void setRotation(float angle) override;
        void setColor(int r, int g, int b) override;
        void setColor(const Vector3i& rgb) override;
        void setColor(const Vector3f& rgb) override;

        void render(Matrix4f screen) override;
    };

}