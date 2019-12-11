#include "Controller.h"

namespace JEngine {

    Controller::Controller(Type type) {
        for (int i = 0; i < GLFW_JOYSTICK_LAST; i++) {
            if (glfwJoystickPresent(i)) {
                _controller = i;
                break;
            }
        }
        _type = type;
    }

    bool Controller::isButtonDown(int button) {
        int temp;
        const unsigned char* buttons = glfwGetJoystickButtons(_controller, &temp);
        return bool(buttons[button]);
    }

    float Controller::getAxis(int axis) {
        const float* axes = getAllAxes();
        return axes[axis];
    }

    const float *Controller::getAllAxes() {
        int temp;
        const float* axes = glfwGetJoystickAxes(_controller, &temp);
        return axes;
    }

    const Controller::Axis& XboxController::leftStick() {
        const float* axes = getAllAxes();
        return {
            axes[1] < 0 ? -axes[1] : 0,
            axes[1] > 0 ?  axes[1] : 0,
            axes[0] < 0 ? -axes[0] : 0,
            axes[0] > 0 ?  axes[0] : 0
        };
    }

    const Controller::Axis &XboxController::rightStick() {
        const float* axes = getAllAxes();
        return {
                axes[3] > 0 ?  axes[3] : 0,
                axes[3] < 0 ?  axes[3] : 0,
                axes[2] < 0 ? -axes[2] : 0,
                axes[2] > 0 ? -axes[2] : 0
        };
    }

    float XboxController::leftTrigger() {
        return getAxis(4);
    }

    float XboxController::rightTrigger() {
        return getAxis(5);
    }

}