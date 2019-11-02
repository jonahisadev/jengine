#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/Scene.h"
#include "../Graphics/Quad.h"

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;

    Display window(800, 600, "JEngine Test v0.5", true);
    window.center();
    window.vsync(true);

    Font text("Roboto-Regular.ttf", 24, &window);

    Scene scene(&window);

    Quad a(100, 100, 64, 64);
    a.setColor(0, 255, 128);
    scene.add(a);

    Quad b(200, 200, 128, 128);
    b.setColor(128, 0, 255);
    scene.add(b);

    auto render = [&](Matrix4f screen) {
        window.clear(0, 128, 128);

        scene.render();

        std::string fps = "FPS: " + std::to_string(window.getFPS());
        text.render(5, text.height(fps) + 5, fps, {1, 1, 1});
    };

    auto update = [&](float delta) {
        if (window.key('D'))
            scene.translateCamera({10 * delta, 0});
        if (window.key('A'))
            scene.translateCamera({-10 * delta, 0});
    };

    window.run(render, update);
    return 0;
}