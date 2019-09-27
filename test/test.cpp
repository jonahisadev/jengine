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
    Display window(800, 600, "JEngine Test v0.4", true);
    window.vsync(true);

    Font text("Roboto-Regular.ttf", 24);

    auto render = [&]() {
        window.clear(0, 128, 128);

        text.render(5, 30, std::to_string(window.width()), {1, 1, 1});
        text.render(5, 60, std::to_string(window.height()), {1, 1, 1});
    };

    auto update = [&](float delta) {
    };

    window.run(render, update);
    return 0;
}