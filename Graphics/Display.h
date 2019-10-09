#pragma once

#include "OpenGL.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../Math/Vector2.h"

#include <iostream>
#include <functional>
#include <cmath>

#include "../Game/Game.h"
#include "../Util/Logger.h"
#include "../Math/Vector.h"
#include "TexturedQuad.h"

namespace JEngine {

    class Display {
    private:
        GLFWwindow* _window;
        Vector2i _size;
        Vector2i _last_size;
        Vector2i _pos;
        int _fps;
        Vector2f _mouse_pos;
        TexturedQuadPtr _mouse_tex;
        unsigned char _keys[350];

        void resize_callback(GLFWwindow* window, int width, int height);
        
    public:
        Display(int width, int height, const char* title, bool resizable);
        virtual ~Display();
        
        bool key(int code);
        bool keyOnce(int code);
        const Vector2f& mousePosition();
        bool mousePressed(int button);
        inline int getFPS() const { return _fps; }
        
        void run(std::function<void()> renderfn, std::function<void(float)> updatefn);
        void clear(int r, int g, int b);
        void close();
        void vsync(bool state);
        void fullscreen(bool state);
        void resize(int width, int height);
        void showCursor(bool state);
        void setCursorImage(const char* path, int size);
        
        inline int width() const { return _size.x(); }
        inline int height() const { return _size.y(); }
        inline int x() const { return _pos.x(); }
        inline int y() const { return _pos.y(); }
    };
    
    enum Key {
        KeyEscape =         256,
        KeyEnter =          257,
        KeyTab =            258,
        KeyBackspace =      259,
        KeyRight =          262,
        KeyLeft =           263,
        KeyDown =           264,
        KeyUp =             265,
        KeyCapsLock =       280,
        KeyLeftShift =      340,
        KeyLeftControl =    341,
        KeyLeftAlt =        342,
        KeyLeftSuper =      343,
        KeyRightShift =     344,
        KeyRightControl =   345,
        KeyRightAlt =       346,
        KeyRightSuper =     347,
        
        KeyF1 =             290,
        KeyF2 =             291,
        KeyF3 =             292,
        KeyF4 =             293,
        KeyF5 =             294,
        KeyF6 =             295,
        KeyF7 =             296,
        KeyF8 =             297,
        KeyF9 =             298,
        KeyF10 =            299,
        KeyF11 =            300,
        KeyF12 =            301,
    };
    
    enum Mouse {
        MouseLeft =     0,
        MouseMiddle =   1,
        MouseRight =    2
    };

}