#include "../JEngine.h"
#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/TexturedQuad.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    using namespace JEngine;
    Display window(800, 600, "JEngine Test v0.2", false);

    Font text("Roboto-Regular.ttf", 24);
    TexturedQuad gradient(100, 100, 64, 64, "gradient.png");

    const char* center_str = "Centered!";
    float center_width = text.width(center_str);
    
    Vector3f white = {1, 1, 1};
    Vector3f black = {0, 0, 0};

    auto render = [&]() {
        window.clear(0, 128, 128);

        text.render(400 - (center_width / 2), 300, center_str, black);

        gradient.render();

        text.render(2, 20, "JEngine v0.2", white);
        std::string fps = std::string("FPS: ") + std::to_string(window.getFPS());
        text.render(2, 42, fps, white);
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