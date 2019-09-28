#pragma once

#include "Mesh.h"
#include "../Math/Vector.h"

namespace JEngine {

    class Quad {
    protected:
        Vector2f _pos;
        Vector2f _size;
        Vector3f _color;
        MeshPtr _mesh;
        
        float _angle;
        
    public:
        Quad(float x, float y, float width, float height);
        virtual ~Quad();
        
        void translate(float dx, float dy);
        void rotate(float dr);
        
        void setPosition(float x, float y);
        void setPosition(const Vector2f& pos);
        void setAngle(float angle);
        void setColor(int r, int g, int b);

        bool intersects(const Quad& other) const;
        static bool intersects(const Quad& a, const Quad& b);
        
        void render();

        inline float x() const { return _pos.x(); }
        inline float y() const { return _pos.y(); }
        inline float width() const { return _size.x(); }
        inline float height() const { return _size.y(); }
        inline float angle() const { return _angle; }
    };

}