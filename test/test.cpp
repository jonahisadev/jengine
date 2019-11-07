#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/Scene.h"
#include "../Graphics/Quad.h"

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;

    Logger logger("Test");

    Display window(800, 600, "JEngine Test v0.5", true);
    window.center();
    window.vsync(true);
    logger.info("Window created!");

    Quad quad(100, 100, 100, 100);
    quad.setColor(192, 192, 192);
    logger.info("Quad created!");

    auto render = [&](Matrix4f screen)
    {
        window.clear(16, 16, 16);

        quad.render(screen);
    };

    auto update = [&](float delta)
    {
        if (quad.intersects(window.mousePosition()))
            quad.setColor(255, 128, 128);
        else
            quad.setColor(192, 192, 192);
    };

    window.run(render, update);
    logger.info("Finished!");
    return 0;
}