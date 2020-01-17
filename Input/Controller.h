#pragma once

#include <GLFW/glfw3.h>

#if defined(JENGINE_WINDOWS)
#define XBOX_LS_H   0
#define XBOX_LS_V   1
#define XBOX_RS_H   2
#define XBOX_RS_V   3
#define XBOX_LT     4
#define XBOX_RT     5
#elif defined(JENGINE_LINUX)
#define XBOX_LS_H   0
#define XBOX_LS_V   1
#define XBOX_LT     2
#define XBOX_RS_H   3
#define XBOX_RS_V   4
#define XBOX_RT     5
#endif

namespace JEngine {

    class Controller {
    public:
        enum Type {
            Generic,
            Xbox
        };
        
        struct Axis {
            float up;
            float down;
            float left;
            float right;
        };
        
    protected:
        Type _type;
        int _controller;
        
    public:
        explicit Controller(Type type);
        virtual ~Controller() {}
        
        bool isButtonDown(int button);
        float getAxis(int axis);
        const float* getAllAxes();
    };
    
    class XboxController : public Controller {
    public:
        enum Buttons {
            A = 0,
            B = 1,
            X = 2,
            Y = 3,
            LB = 4,
            RB = 5,
            Select = 6,
            Start = 7,
#if defined(JENGINE_WINDOWS)
            LeftStick = 8,
            RightStick = 9,
            DPADUp = 10,
            DPADRight = 11,
            DPADDown = 12,
            DPADLeft = 13,
#elif defined(JENGINE_LINUX)
            Xbox = 8,
            LeftStick = 9,
            RightStick = 10,
            DPADUp = 11,
            DPADRight = 12,
            DPADDown = 13,
            DPADLeft = 14,
#endif
        };
        
        explicit XboxController() : Controller(Type::Xbox) {}
        virtual ~XboxController() {}
        
        const Axis* leftStick();
        const Axis* rightStick();
        float leftTrigger();
        float rightTrigger();
    };

}