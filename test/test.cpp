#include "../JEngine.h"
#include "../Game/Game.h"

#include "../Graphics/Display.h"
#include "../Graphics/Font.h"
#include "../Graphics/Scene.h"
#include "../Graphics/Quad.h"
#include "../Graphics/Light.h"

int main(int argc, char** argv) {
    using namespace JEngine;

    Game::flags() << Game::EnableFonts;

    Display window(800, 600, "JEngine Test v0.5", true);
    window.center();
    window.vsync(true);

    bool debug = false;

    Font text("Roboto-Regular.ttf", 14, &window);

    Scene scene(&window);

    Quad a(100, 100, 64, 64);
    a.setColor(128, 128, 128);
    a.setBlocksLight(true);
    scene.add(a);

    Quad b(200, 200, 128, 128);
    b.setColor(128, 128, 128);
    b.setBlocksLight(true);
    // scene.add(b);

    Light light(0, 0, 800, {1, 1, 1});
    light.setCenter(350, 150);
    scene.add(light);

    auto render = [&](Matrix4f screen) {
        window.clear(8, 8, 8);

        scene.render();

        if (debug) {
            const char* ver = "JEngine v0.5";
            text.render(5, text.height(ver) + 5, ver, {1, 1, 1});
            std::string fps = "FPS: " + std::to_string(window.getFPS());
            text.render(5, text.height(fps) + text.height(ver) + 10, fps, {1, 1, 1});
        }
    };

    auto update = [&](float delta) {
        if (window.key('D'))
            a.translate(10 * delta, 0);
        if (window.key('A'))
            a.translate(-10 * delta, 0);

        if (window.mousePressed(Mouse::MouseLeft)) {
            auto vec = window.mousePosition();
            light.setCenter(vec.x(), vec.y());
        }

        if (window.keyOnce(Key::KeyF3))
            debug = !debug;
    };

    window.run(render, update);
    return 0;
}
