#include "../JEngine.h"
#include "../Display.h"
#include "../Quad.h"
#include <iostream>

int main(int argc, char** argv) {
    using namespace JEngine;

    Display window(800, 600, "Jengine Test 0.1", false);

    Quad square(100, 100, 100, 100);

    auto render = [&]() {
        window.clear(0, 128, 255);
        square.render();
    };

    auto update = [&](float delta) {
        if (window.key('D'))
            square.translate(20 * delta, 0);
        if (window.key('A'))
            square.translate(-20 * delta, 0);
        if (window.key('S'))
            square.translate(0, 20 * delta);
        if (window.key('W'))
            square.translate(0, -20 * delta);
    };

    window.run(render, update);
    return 0;
}