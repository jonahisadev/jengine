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

    auto render = [&](Matrix4f screen)
    {
        window.clear(16, 16, 16);
        quad.render(screen);

        if (debug) {
            std::string fps = "FPS: " + std::to_string(window.getFPS());
            font.render(5, 25, fps, {1, 1, 1});
        }
    };

    auto update = [&](float delta)
    {
        if (window.key('D'))
            quad.translate(20 * delta, 0);
        if (window.key('A'))
            quad.translate(-20 * delta, 0);
        if (window.key('S'))
            quad.translate(0, 20 * delta);
        if (window.key('W'))
            quad.translate(0, -20 * delta);

        if (window.key('R'))
            quad.rotate(25 * delta);

        if (quad.intersects(window.mousePosition()))
            quad.setColor(255, 0, 0);
        else
            quad.setColor(255, 255, 255);

        debug = window.key(Key::KeyF4);
    };

    window.run(render, update);
    return 0;
}