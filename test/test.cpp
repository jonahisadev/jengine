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
    Quad me(100, 100, 50, 50);
    Quad other(500, 500, 75, 75);
    other.setColor(64, 64, 64);

    auto render = [&]() {
        window.clear(0, 128, 128);

        other.render();
        me.render();

        if (Quad::intersects(me, other))
            text.render(5, 30, "Intersecting", {1, 1, 1});
        else
            text.render(5, 30, "Not intersecting", {1, 1, 1});
    };

    auto update = [&](float delta) {
        if (window.key('D'))
            me.translate(15 * delta, 0);
        if (window.key('A'))
            me.translate(-15 * delta, 0);
        if (window.key('S'))
            me.translate(0, 15 * delta);
        if (window.key('W'))
            me.translate(0, -15 * delta);
    };

    window.run(render, update);
    return 0;
}