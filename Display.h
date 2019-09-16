#pragma once

#include "OpenGL.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <functional>

namespace Jengine {

    class Display {
    private:
        GLFWwindow* _window;
        int _width, _height;
        
    public:
        Display(int width, int height, const char* title, bool resizable);
        virtual ~Display();
        
        bool key(int code);
        
        void run(std::function<void()> renderfn, std::function<void(float)> updatefn);
        void clear(int r, int g, int b);
        void close();
    };

}