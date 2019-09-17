#include "Display.h"

namespace JEngine {

    Display::Display(int width, int height, const char *title, bool resizable) 
    : _width(width), _height(height), _fps(0)
    {
        if (!glfwInit())
            throw "Could not initialize GLFW";
        
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        
        _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!_window) {
            glfwTerminate();
            throw "Could not create GLFW window";
        }
        
        glfwMakeContextCurrent(_window);

#ifdef JENGINE_WINDOWS
        if (glewInit() != GLEW_OK) {
            std::cerr << "Could not initialize GLEW" << std::endl;
            throw;
        }  
#endif
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    Display::~Display() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    bool Display::key(int code) {
        return glfwGetKey(_window, code) == GLFW_PRESS;
    }

    const Vector2f& Display::mousePosition() {
        double x, y;
        glfwGetCursorPos(_window, &x, &y);
        Vector2f::Ptr vec = std::make_shared<Vector2f>(float(x), float(y));
        return *vec.get();
    }

    bool Display::mousePressed(int button) {
        return glfwGetMouseButton(_window, button) == GLFW_PRESS;
    }

    void Display::run(std::function<void()> renderfn, std::function<void(float)> updatefn) {
        float delta = 1.0f;
        int frames = 0;
        double fps_time = glfwGetTime();
        
        while (!glfwWindowShouldClose(_window)) {
            double last = glfwGetTime();
            
            updatefn(delta);
            renderfn();
            
            glfwSwapBuffers(_window);
            glfwPollEvents();
            
            double now = glfwGetTime();
            delta = float(now - last) * 10.0f;

            // FPS calculator
            frames++;
            if (now - fps_time >= 1.0) {
                _fps = frames;
                frames = 0;
                fps_time = now;
            }
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