#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/TexturedQuad.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;
    Display window(800, 600, "JEngine Test v0.4", false);
    window.vsync(true);

    Font text("Roboto-Regular.ttf", 24);
    TexturedQuad gradient(100, 100, 64, 64, "gradient.png");

    auto render = [&]() {
        window.clear(0, 128, 128);
        gradient.render();

        std::string fps = std::to_string(window.getFPS());
        text.render(5, text.height(fps) + 5, fps, {1, 1, 1});
    };

    auto update = [&](float delta) {
        if (window.mousePressed(0)) {
            Vector2f mouse = window.mousePosition();
            mouse.translate(-32, -32);
            gradient.setPosition({mouse.x(), mouse.y()});
        }

        gradient.rotate(10 * delta);
    };

    window.run(render, update);
    return 0;
}