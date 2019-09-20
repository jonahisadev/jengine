#pragma once

#include "OpenGL.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../Math/Vector2.h"

#include <iostream>
#include <functional>

namespace JEngine {

    class Display {
    private:
        GLFWwindow* _window;
        int _width, _height;
        int _fps;
        
    public:
        Display(int width, int height, const char* title, bool resizable);
        virtual ~Display();
        
        bool key(int code);
        const Vector2f& mousePosition();
        bool mousePressed(int button);
        inline int getFPS() const { return _fps; }
        
        void run(std::function<void()> renderfn, std::function<void(float)> updatefn);
        void clear(int r, int g, int b);
        void close();
        
        inline int width() const { return _width; }
        inline int height() const { return _height; }
    };

}