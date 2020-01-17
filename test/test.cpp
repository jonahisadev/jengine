#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/Quad.h"
#include "../Graphics/TextGroup.h"
#include "../Input/Controller.h"

#include <string>

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;

    Display window(800, 600, "JEngine Test v0.5", true);
    window.center();
    window.vsync(true);

    TexturedQuad quad(100, 100, 128, 128, "coyote.png");
    float speed = 35.0f;

    Font font("Roboto-Regular.ttf", 18, &window);
    bool debug = false;

    XboxController controller;

    auto render = [&](Matrix4f screen)
    {
        window.clear(16, 16, 16);
        quad.render(screen);

        if (debug) {
            int count;
            const float* buttons = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
            std::string btns = "(" + std::to_string(count) + "): ";
            for (int i = 0; i < count; i++) {
                btns += std::to_string(buttons[i]) + " ";
            }

            font.render(5, 25, btns, {1, 1, 1});
        }
    };

    auto update = [&](float delta)
    {
        quad.translate(speed * delta * controller.leftStick()->right, 0);
        quad.translate(-speed * delta * controller.leftStick()->left, 0);
        quad.translate(0, speed * delta * controller.leftStick()->down);
        quad.translate(0, -speed * delta * controller.leftStick()->up);

        quad.rotate(controller.rightTrigger() * delta * 25.0f);
        quad.rotate(-controller.leftTrigger() * delta * 25.0f);

        debug = controller.isButtonDown(XboxController::RB);
    };

    window.run(render, update);
    return 0;
}