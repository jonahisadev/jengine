#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/TexturedQuad.h"
#include "../Graphics/Spritesheet.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;
    Display window(800, 600, "JEngine Test v0.4", true);
    window.center();
    window.vsync(true);

    Font text("Roboto-Regular.ttf", 24);

    // TexturedQuad sheet(100, 100, 200, 200, "coyote.png");
    // bool linear = true;
    // sheet.linearInterp(linear);

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
    };

    window.run(render, update);
    return 0;
}