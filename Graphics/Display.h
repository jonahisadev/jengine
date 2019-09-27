#pragma once

#include "OpenGL.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../Math/Vector2.h"

#include <iostream>
#include <functional>

#include "../Game/Game.h"
#include "../Util/Logger.h"

namespace JEngine {

    class Display {
    private:
        GLFWwindow* _window;
        int _width, _height;
        int _fps;

        void resize_callback(GLFWwindow* window, int width, int height);
        
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
        void vsync(bool state);
        
        inline int width() const { return _width; }
        inline int height() const { return _height; }
    };

}