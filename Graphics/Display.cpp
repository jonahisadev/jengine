#include "Display.h"
#include "Font.h"
#include "../Audio/Audio.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace JEngine {

    Display::Display(int width, int height, const char *title, bool resizable) 
    : _width(width), _height(height), _fps(0)
    {
        if (!glfwInit()) {
            JERROR("Could not initialize GLFW");
            throw;
        }
        
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        
        _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!_window) {
            glfwTerminate();
            JERROR("Could not create GLFW window");
            throw;
        }

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);

        // Resize callback
        auto func = [](GLFWwindow* w, int width, int height) {
            static_cast<Display*>(glfwGetWindowUserPointer(w))->resize_callback(w, width, height);
        };
        glfwSetWindowSizeCallback(_window, func);

#ifdef JENGINE_WINDOWS
        if (glewInit() != GLEW_OK) {
            std::cerr << "Could not initialize GLEW" << std::endl;
            throw;
        }  
#endif
        resize_callback(_window, width, height);
        
        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    Display::~Display() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void Display::resize_callback(GLFWwindow *window, int width, int height) {
        _width = width;
        _height = height;
        int fb_width, fb_height;
        glfwGetFramebufferSize(window, &fb_width, &fb_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
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
        Game::init();
        
        float delta = 1.0f;
        int frames = 0;
        double fps_time = glfwGetTime();
        
        while (!glfwWindowShouldClose(_window)) {
            double last = glfwGetTime();
            
            updatefn(delta);
            renderfn();
            
            glfwSwapBuffers(_window);
            glfwPollEvents();

            Audio::audioLoop();
            
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
        
        Game::cleanup();
    }

    void Display::clear(int r, int g, int b) {
        glClearColor(r/255.0f, g/255.0f, b/255.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Display::close() {
        glfwSetWindowShouldClose(_window, true);
    }

    void Display::vsync(bool state) {
        glfwSwapInterval(state);
    }

}