#pragma once

#include <GLFW/glfw3.h>

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
            DPADUp = 10,
            DPADRight = 11,
            DPADDown = 12,
            DPADLeft = 13,
            LeftStick = 8,
            RightStick = 9
        };
        
        explicit XboxController() : Controller(Type::Xbox) {}
        virtual ~XboxController() {}
        
        const Axis& leftStick();
        const Axis& rightStick();
        float leftTrigger();
        float rightTrigger();
    };

}