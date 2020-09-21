#include "Display.h"
#include "Font.h"
#include "../Audio/Audio.h"
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../Game/BaseGame.h"

namespace JEngine {

    Display::Display(int width, int height, const std::string& title, bool resizable)
            : _size({width, height}), _fps(0), _title(title), _mouse_tex(nullptr)
    {
        if (!glfwInit()) {
            JERROR("Could not initialize GLFW");
            throw;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef JENGINE_MACOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        glfwWindowHint(GLFW_SAMPLES, 4);

        _window = glfwCreateWindow(width, height, "Loading...", nullptr, nullptr);
        if (!_window) {
            glfwTerminate();
            JERROR("Could not create GLFW window");
            throw;
        }

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);

        JINFO("OpenGL Version: %s", glGetString(GL_VERSION));
        JINFO("Graphics Card: %s", glGetString(GL_RENDERER));

        // Resize callback
        auto resize = [](GLFWwindow* w, int width, int height) {
            static_cast<Display*>(glfwGetWindowUserPointer(w))->resize_callback(w, width, height);
        };
        glfwSetWindowSizeCallback(_window, resize);

        // Mouse position callback
        auto mouse_pos = [](GLFWwindow* w, double x, double y) {
            auto d = static_cast<Display*>(glfwGetWindowUserPointer(w));
            d->_mouse_pos = {float(x), float(y)};
            if (d->_mouse_tex)
                d->_mouse_tex->setCenter(d->_mouse_pos);
        };
        glfwSetCursorPosCallback(_window, mouse_pos);

        // Window position callback
        auto window_pos = [](GLFWwindow* w, int x, int y) {
            auto d = static_cast<Display*>(glfwGetWindowUserPointer(w));
            d->_pos = {x, y};
        };
        glfwSetWindowPosCallback(_window, window_pos);

        #ifdef JENGINE_WINDOWS
        if (glewInit() != GLEW_OK) {
            JERROR("Could not initialize GLEW");
            throw;
        }
        #endif
        resize_callback(_window, width, height);

        // Save position
        int x, y;
        glfwGetWindowPos(_window, &x, &y);
        _pos = {x, y};

        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_MULTISAMPLE);
    }

    Display::~Display()
    {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void Display::resize_callback(GLFWwindow* window, int width, int height)
    {
        _size = {width, height};
        int fb_width, fb_height;
        glfwGetFramebufferSize(window, &fb_width, &fb_height);
        glViewport(0, 0, fb_width, fb_height);
        _projection = glm::ortho(0.0f, float(width), float(height), 0.0f, -1.0f, 1.0f);
    }

    GLFWmonitor* Display::getMonitorByIndex(int monitor)
    {
        GLFWmonitor* mtr;
        if (monitor < 0)
            mtr = glfwGetPrimaryMonitor();
        else {
            int count;
            GLFWmonitor** mtrs = glfwGetMonitors(&count);
            if (monitor >= count) {
                JERROR("Monitor index out of range! (%d >= %d)", monitor, count);
                return nullptr;
            }

            mtr = mtrs[monitor];
        }
        return mtr;
    }

    bool Display::key(int code)
    {
        return glfwGetKey(_window, code) == GLFW_PRESS;
    }

    bool Display::keyOnce(int code)
    {
        if (key(code) && !_keys[code]) {
            _keys[code] = true;
            return true;
        }

        if (!key(code)) { _keys[code] = false; }
        return false;
    }

    const Vector2f& Display::mousePosition()
    {
        return _mouse_pos;
    }

    bool Display::mousePressed(int button)
    {
        return glfwGetMouseButton(_window, button) == GLFW_PRESS;
    }

    bool Display::mousePressedOnce(int button)
    {
        if (mousePressed(button) && !_mouse[button]) {
            _mouse[button] = true;
            return true;
        }

        if (!mousePressed(button)) { _mouse[button] = false; }
        return false;
    }

    void Display::run(BaseGame* game, std::function<void(Matrix4f)> renderfn, std::function<void(float)> updatefn)
    {
        game->init();

        float delta = 1.0f;
        int frames = 0;
        double fps_time = glfwGetTime();

        glfwSetWindowTitle(_window, _title.c_str());

        while (!glfwWindowShouldClose(_window)) {
            double last = glfwGetTime();

            Animate::run(delta);

            updatefn(delta);
            renderfn(_projection * glm::mat4(1.0f));

            if (_mouse_tex)
                _mouse_tex->render(_projection * glm::mat4(1.0f));

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
    }

    void Display::clear(int r, int g, int b)
    {
        glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Display::clear(const Vector3i& vec)
    {
        clear(vec.r(), vec.g(), vec.b());
    }

    void Display::close()
    {
        glfwSetWindowShouldClose(_window, true);
    }

    void Display::vsync(bool state)
    {
        glfwSwapInterval(state);
    }

    void Display::fullscreen(bool state)
    {
        if (state) {
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            Vector2i last_pos = _pos;
            _last_size = _size;
            glfwSetWindowMonitor(_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
            _pos = last_pos;
        } else {
            glfwSetWindowMonitor(_window, nullptr, _pos.x(), _pos.y(), _last_size.x(), _last_size.y(), GLFW_DONT_CARE);
        }
    }

    void Display::setPosition(int x, int y, int monitor)
    {
        GLFWmonitor* mtr = getMonitorByIndex(monitor);
        if (!mtr) return;

        int vx, vy;
        glfwGetMonitorPos(mtr, &vx, &vy);
        glfwSetWindowPos(_window, x + vx, y + vy);
    }

    void Display::setPosition(const Vector2i& pos, int monitor)
    {
        setPosition(pos.x(), pos.y(), monitor);
    }

    void Display::center(int monitor)
    {
        GLFWmonitor* mtr = getMonitorByIndex(monitor);
        if (!mtr) return;

        const GLFWvidmode* vidmode = glfwGetVideoMode(mtr);
        setPosition((vidmode->width / 2) - (width() / 2), (vidmode->height / 2) - (height() / 2), monitor);
    }

    void Display::resize(int width, int height)
    {
        glfwSetWindowSize(_window, width, height);
    }

    void Display::showCursor(bool state)
    {
        glfwSetInputMode(_window, GLFW_CURSOR, state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
    }

    void Display::setCursorImage(const char* path, int size)
    {
        if (!path || size == 0) {
            delete _mouse_tex;
            showCursor(true);
        } else {
            _mouse_tex = new TexturedQuad(0, 0, size, size, path);
            _mouse_tex->setCenter(_mouse_pos);
            showCursor(false);
        }
    }

}
