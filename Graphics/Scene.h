#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Quad.h"
#include "Display.h"

namespace JEngine {

    class Scene {
    private:
        std::vector<Quad> _items;
        const glm::mat4& _projection;
        glm::mat4 _view;
        
    public:
        Scene(Display* d);
        ~Scene();
        
        void add(Quad& item);
        void render();
        
        void translate(const Vector2f& vec);
        void translateCamera(const Vector2f& vec);
    };

}