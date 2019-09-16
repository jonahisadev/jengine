#include "../JEngine.h"
#include "../Display.h"
#include "../Mesh.h"
#include <iostream>

int main(int argc, char** argv) {
    using namespace JEngine;

    Display window(800, 600, "Jengine Test 0.1", false);

    float pos[] = {
        100, 100,
        200, 100,
        200, 200,
        100, 200
    };

    float color[] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        1, 1, 1
    };

    int els[] = {
        0, 1, 2,
        0, 3, 2
    };

    Mesh mesh(pos, color, els, 4, 6);

    auto render = [&]() {
        window.clear(0, 128, 255);
        mesh.render();
    };

    auto update = [&](float delta) {};

    window.run(render, update);
    return 0;
}