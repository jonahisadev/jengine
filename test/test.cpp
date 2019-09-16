#include "../Display.h"
#include "../Vertex2.h"
#include <iostream>

int main(int argc, char** argv) {
    using namespace Jengine;

    Display window(800, 600, "Jengine Test 0.1", false);

    auto render = [&]() {
        if (window.key('Q'))
            window.clear(0, 255, 128);
        else if (window.mousePressed(0))
            window.clear(255, 0, 128);
        else
            window.clear(0, 128, 255);
    };

    auto update = [&](float delta) {
        const Vertex2& pos = window.mousePosition();
        std::cout << pos.x() << ", " << pos.y() << std::endl;
    };

    window.run(render, update);
    return 0;
}