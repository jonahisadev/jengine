#include "../JEngine.h"
#include "../Display.h"
#include "../TexturedQuad.h"
#include <iostream>

int main(int argc, char** argv) {
    using namespace JEngine;
    Display window(800, 600, "Jengine Test 0.1", false);

    TexturedQuad gradient(100, 100, 64, 64, "gradient.png");

    auto render = [&]() {
        window.clear(0, 128, 128);
        gradient.render();
    };

    auto update = [&](float delta) {
        gradient.translate(5 * delta, 0);
    };

    window.run(render, update);
    return 0;
}