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
#include <cmath>

#define PI 3.14159265

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;
    Game::setResourceLocation("res");

    Display window(800, 600, "JEngine Test v0.5", true);
    window.center();
    window.vsync(true);

    TexturedQuad quad(100, 100, 100, 100, Game::resource("coyote.png"));
    TexturedQuad grid(0, 0, 800, 600, Game::resource("grid.png"));
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
        grid.render(screen);
        quad.render(screen);

        if (debug) {
            std::string fps = "FPS: " + std::to_string(window.getFPS());
            font.render(5, 20, fps, {0, 0, 0});
            std::string d = "Delta: " + std::to_string(_delta);
            font.render(5, 40, d, {0, 0, 0});
            std::string pos = "(" + std::to_string(quad.x()) + ", " + std::to_string(quad.y()) + ")";
            font.render(5, 60, pos, {0, 0, 0});
        }
    };

    bool filter = false;

    auto quad_move = [&](const Vector2f& dv) { quad.translate(dv); };

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

        if (window.keyOnce(KeyEscape))
            sound.applyFilter((filter = !filter));

        // Animations
        if (window.keyOnce(KeyRight)) {
            Animate::linear({quad.x(), quad.y()}, {quad.x() + 100, quad.y()}, 250, quad_move);
        }
        if (window.keyOnce(KeyLeft)) {
            Animate::linear({quad.x(), quad.y()}, {quad.x() - 100, quad.y()}, 250, quad_move);
        }
        if (window.keyOnce(KeyDown)) {
            Animate::linear({quad.x(), quad.y()}, {quad.x(), quad.y() + 100}, 250, quad_move);
        }
        if (window.keyOnce(KeyUp)) {
            Animate::linear({quad.x(), quad.y()}, {quad.x(), quad.y() - 100}, 250, quad_move);
        }

        // Rotation example
        if (window.keyOnce('R')) {
            Animate::singleVar(0, 360, 1000, [&](float dr) {
                quad.rotate(dr);
            });
        }

        if (window.keyOnce(KeyF4))
            debug = !debug;
    };

    window.run(render, update);
    return 0;
}