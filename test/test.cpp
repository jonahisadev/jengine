#include "../JEngine.h"
#include "../Graphics/Display.h"
#include "../Graphics/TexturedQuad.h"
#include "../Math/Vector.h"
#include <iostream>

int main(int argc, char** argv) {
    using namespace JEngine;
    
    Display window(800, 600, "Jengine Test 0.1", false);
    TexturedQuad gradient(100, 100, 64, 64, "gradient.png");

    Vector3f a = {0, 1, 2};
    Vector3f b = {-2, 5, 8};

    std::cout << Vector3f::distance(a, b) << std::endl;

    auto render = [&]() {
        window.clear(0, 128, 128);
        gradient.render();
    };

    auto update = [&](float delta) {
        if (window.key('D'))
            gradient.translate(15 * delta, 0);
        if (window.key('A'))
            gradient.translate(-15 * delta, 0);
        if (window.key('S'))
            gradient.translate(0, 15 * delta);
        if (window.key('W'))
            gradient.translate(0, -15 * delta);
    };

    window.run(render, update);
    return 0;
}