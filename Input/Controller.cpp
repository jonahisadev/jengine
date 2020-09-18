#include "Controller.h"

namespace JEngine {

    Controller::Controller(Type type)
            : _controller(-1)
    {
        for (int i = 0; i < GLFW_JOYSTICK_LAST; i++) {
            if (glfwJoystickPresent(i)) {
                _controller = i;
                _type = type;
                break;
            }
        }

        if (_controller < 0)
            throw;
    }

    bool Controller::isButtonDown(int button)
    {
        int temp;
        const unsigned char* buttons = glfwGetJoystickButtons(_controller, &temp);
        return bool(buttons[button]);
    }

    float Controller::getAxis(int axis)
    {
        const float* axes = getAllAxes();
        return axes[axis];
    }

    const float* Controller::getAllAxes()
    {
        int temp;
        const float* axes = glfwGetJoystickAxes(_controller, &temp);
        return axes;
    }

    const Controller::Axis* XboxController::leftStick()
    {
        const float* axes = getAllAxes();
        return new Axis{
                axes[XBOX_LS_V] < 0 ? -axes[XBOX_LS_V] : 0,
                axes[XBOX_LS_V] > 0 ? axes[XBOX_LS_V] : 0,
                axes[XBOX_LS_H] < 0 ? -axes[XBOX_LS_H] : 0,
                axes[XBOX_LS_H] > 0 ? axes[XBOX_LS_H] : 0
        };
    }

    const Controller::Axis* XboxController::rightStick()
    {
        const float* axes = getAllAxes();
        return new Axis{
                axes[XBOX_RS_V] > 0 ? axes[XBOX_RS_V] : 0,
                axes[XBOX_RS_V] < 0 ? axes[XBOX_RS_V] : 0,
                axes[XBOX_RS_H] < 0 ? -axes[XBOX_RS_H] : 0,
                axes[XBOX_RS_H] > 0 ? -axes[XBOX_RS_H] : 0
        };
    }

    float XboxController::leftTrigger()
    {
        return getAxis(XBOX_LT);
    }

    float XboxController::rightTrigger()
    {
        return getAxis(XBOX_RT);
    }

}