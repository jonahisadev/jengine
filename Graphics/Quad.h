#pragma once

#include <memory>

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
        void translate(const Vector2f& vec);
        void rotate(float dr);
        
        void setPosition(float x, float y);
        void setPosition(const Vector2f& pos);
        void setAngle(float angle);
        void setColor(int r, int g, int b);
        void setColor(const Vector3i& rgb);
        void setColor(const Vector3f& rgb);
        void setCenter(Vector2f center);

        bool intersects(const Quad& other) const;
        bool intersects(const Vector2f& vec) const;
        static bool intersects(const Quad& a, const Quad& b);
        static bool intersects(const Quad& quad, const Vector2f& vec);
        
        void render(Matrix4f screen);

        inline float x() const { return _pos.x(); }
        inline float y() const { return _pos.y(); }
        inline float width() const { return _size.x(); }
        inline float height() const { return _size.y(); }
        inline float angle() const { return _angle; }
    };
    
    typedef std::shared_ptr<Quad> QuadPtr;

}