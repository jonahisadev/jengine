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

    std::vector<TexturedQuad> quads;

    auto render = [&]() {
        window.clear(0, 128, 128);

        for (auto& quad : quads) {
            quad.render();
        }

        std::string fps = "FPS: " + std::to_string(window.getFPS());
        text.render(5, text.height(fps) + 5, fps, {1, 1, 1});

        std::string count = "Count: " + std::to_string(quads.size());
        text.render(5, 2 * (text.height(fps) + 5), count, {1, 1, 1});
    };

    auto update = [&](float delta) {
        if (window.keyOnce(Key::KeyEscape)) {
            window.fullscreen(false);
        }

        if (window.keyOnce('F')) {
            window.fullscreen(true);
        }

        if (window.mousePressedOnce(MouseLeft)) {
            TexturedQuad sheet(0, 0, 100, 100, "coyote.png");
            sheet.setCenter(window.mousePosition());
            sheet.linearInterp(true);
            quads.push_back(sheet);
        }

        if (window.keyOnce('V')) {
            window.vsync(false);
        }

        for (auto& quad : quads) {
            quad.rotate(5 * delta);
        }
    };

    window.run(render, update);
    return 0;
}