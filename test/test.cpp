#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/TexturedQuad.h"
#include "../Graphics/Spritesheet.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;
    Display window(800, 600, "JEngine Test v0.4", true);
    window.vsync(true);

    Font text("Roboto-Regular.ttf", 24);
    // TexturedQuad gradient(100, 100, 64, 64, "spritesheet.png");

    // Spritesheet sheet(100, 100, 128, 128, "spritesheet.png", 32);
    // sheet.setGridPosition(1, 1);
    TexturedQuad sheet(100, 100, 400, 400, "coyote.png");
    bool linear = true;
    sheet.linearInterp(linear);

    auto render = [&]() {
        window.clear(0, 128, 128);
        sheet.render();

        std::string fps = std::to_string(window.getFPS());
        text.render(5, text.height(fps) + 5, fps, {1, 1, 1});
    };

    auto update = [&](float delta) {
        if (window.mousePressed(Mouse::MouseLeft)) {
            sheet.setCenter(window.mousePosition());
        }

        if (window.keyOnce(Key::KeyEscape)) {
            window.fullscreen(false);
        }

        if (window.keyOnce('F')) {
            window.fullscreen(true);
        }

        if (window.keyOnce('Q')) {
            linear = !linear;
            sheet.linearInterp(linear);
        }

        // sheet.rotate(2 * delta);
    };

    window.run(render, update);
    return 0;
}