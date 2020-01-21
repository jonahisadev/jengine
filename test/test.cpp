#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/Quad.h"
#include "../Graphics/TextGroup.h"
#include "../Input/Controller.h"
#include "../Audio/Sound.h"
#include "../Graphics/Animate.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;
    Game::setResourceLocation("res");

    Display window(800, 600, "JEngine Test v0.5", true);
    window.center();
    window.vsync(true);

    TexturedQuad quad(100, 100, 128, 128, Game::resource("coyote.png"));
    float speed = 35.0f;

    Font font(Game::resource("Roboto-Regular.ttf"), 18, &window);
    bool debug = false;

    Audio::initialize();
    Sound sound(Game::resource("daniel.wav"));
    Audio::playSound(sound, 50, true);
    float _delta;

    auto render = [&](Matrix4f screen)
    {
        window.clear(16, 16, 16);
        quad.render(screen);

        if (debug) {
            std::string d = "Delta: " + std::to_string(_delta);
            font.render(5, 25, d, {1, 1, 1});
            std::string pos = "(" + std::to_string(quad.x()) + ", " + std::to_string(quad.y()) + ")";
            font.render(5, 50, pos, {1, 1, 1});
        }
    };

    bool filter = false;

    auto update = [&](float delta)
    {
        _delta = delta;

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

        if (window.keyOnce(KeyEscape))
            sound.applyFilter((filter = !filter));

        if (window.keyOnce(KeyRightShift)) {
            Animate::linear({quad.x(), quad.y()}, {300, 100}, 2000, [&](const Vector2f& dv) {
                quad.translate(dv);
            });
        }

        if (window.keyOnce(KeyF4))
            debug = !debug;
    };

    window.run(render, update);
    return 0;
}