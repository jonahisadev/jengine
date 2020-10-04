#pragma once

#include <memory>

#include "Mesh.h"
#include "../Math/Vector.h"

namespace JEngine {

    class Quad
    {
    protected:
        Vector2f _pos;
        Vector2f _size;
        Vector3f _color;
        float _angle;
        
    public:
        Quad(float x, float y, float width, float height);
        virtual ~Quad();
        
        virtual void translate(float dx, float dy);
        virtual void translate(const Vector2f& vec);
        virtual void rotate(float dr);

        virtual void setPosition(float x, float y);
        virtual void setPosition(const Vector2f& pos);
        virtual void setSize(float width, float height);
        virtual void setSize(Vector2f size);
        virtual void setRotation(float angle);
        virtual void setColor(int r, int g, int b);
        virtual void setColor(const Vector3i& rgb);
        virtual void setColor(const Vector3f& rgb);
        virtual void setCenter(Vector2f center);

        bool intersects(const Quad& other) const;
        bool intersects(const Vector2f& vec) const;
        static bool intersects(const Quad& a, const Quad& b);
        static bool intersects(const Quad& quad, const Vector2f& vec);
        
        virtual void render(Matrix4f screen) = 0;

        inline const Vector2f& position() const { return _pos; }
        inline float x() const { return _pos.x(); }
        inline float y() const { return _pos.y(); }
        inline float width() const { return _size.x(); }
        inline float height() const { return _size.y(); }
        inline float angle() const { return _angle; }
        inline Vector3f color() const { return _color; }
    };

}