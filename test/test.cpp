#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/Quad.h"
#include "../Graphics/TextGroup.h"

#include <string>

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;

    Display window(800, 600, "JEngine Test v0.5", true);
    window.center();
    window.vsync(true);

    Quad quad(100, 100, 100, 100);
    quad.setColor(192, 192, 192);
    
    Font font("Roboto-Regular.ttf", 16, &window);
    TextGroup debug(font, {1, 1, 1}, 10);

    auto render = [&](Matrix4f screen)
    {
        window.clear(16, 16, 16);

        quad.render(screen);

        debug.add("JEngine v0.5b");
        debug.add("FPS: " + std::to_string(window.getFPS()));
        debug.render(10, 10);
        debug.reset();
    };

    auto update = [&](float delta)
    {
        if (quad.intersects(window.mousePosition()))
            quad.setColor(255, 128, 128);
        else
            quad.setColor(192, 192, 192);
    };

    window.run(render, update);
    return 0;
}