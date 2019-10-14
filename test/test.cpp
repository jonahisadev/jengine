#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/TexturedQuad.h"
#include "../Graphics/Spritesheet.h"
#include "../Graphics/UI/TextField.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;
    Display window(800, 600, "JEngine Test v0.4", true);
    window.vsync(true);

    Font text("Roboto-Regular.ttf", 24);
    TextField name(100, 100, "Roboto-Regular.ttf");
    name.install(window);

    auto render = [&]() {
        window.clear(0, 128, 128);

        name.render();

        std::string fps = std::to_string(window.getFPS());
        text.render(5, text.height(fps) + 5, fps, {1, 1, 1});
    };

    auto update = [&](float delta) {
        
    };

    window.run(render, update);
    return 0;
}