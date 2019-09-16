#include "Display.h"

namespace Jengine {

    Display::Display(int width, int height, const char *title, bool resizable) 
    : _width(width), _height(height)
    {
        if (!glfwInit())
            throw "Could not initialize GLFW";
        
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        
        _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!_window) {
            glfwTerminate();
            throw "Could not create GLFW window";
        }
        
        // TODO: GLEW stuff for windows here
        
        glfwMakeContextCurrent(_window);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    Display::~Display() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    bool Display::key(int code) {
        return glfwGetKey(_window, code) == GLFW_PRESS;
    }

    const Vertex2& Display::mousePosition() {
        double x, y;
        glfwGetCursorPos(_window, &x, &y);
        Vertex2Ptr vec = std::make_shared<Vertex2>(float(x), float(y));
        return *vec.get();
    }

    bool Display::mousePressed(int button) {
        return glfwGetMouseButton(_window, button) == GLFW_PRESS;
    }

    void Display::run(std::function<void()> renderfn, std::function<void(float)> updatefn) {
        while (!glfwWindowShouldClose(_window)) {
            updatefn(1.0f);
            renderfn();
            
            glfwSwapBuffers(_window);
            glfwPollEvents();
        }
    }

    void Display::clear(int r, int g, int b) {
        glClearColor(r/255.0f, g/255.0f, b/255.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Display::close() {
        glfwSetWindowShouldClose(_window, true);
    }

}