#include "../Display.h"

int main(int argc, char** argv) {
    using namespace Jengine;

    Display window(800, 600, "Jengine Test 0.1", false);

    auto render = [&]() {
        if (window.key('Q'))
            window.clear(0, 255, 128);
        else
            window.clear(0, 128, 255);
    };

    auto update = [&](float delta) {

    };

    window.run(render, update);
    return 0;
}