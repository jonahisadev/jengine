#include "../JEngine.h"
#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/TexturedQuad.h"
#include "../Audio/Audio.h"
#include "../Audio/Sound.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    using namespace JEngine;
    Display window(800, 600, "JEngine Test v0.3", false);

    Font text("Roboto-Regular.ttf", 24);
    TexturedQuad gradient(100, 100, 64, 64, "gradient.png");

    Audio::initialize();

    Sound sound("test.wav");
    Audio::playSound(sound, 10);

    auto render = [&]() {
        window.clear(0, 128, 128);

        gradient.render();

        std::string fps = "FPS: " + std::to_string(window.getFPS());
        text.render(5, 5 + text.height(fps), fps, {1, 1, 1});
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

    Audio::cleanup();
    return 0;
}