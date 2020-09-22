#include "../JEngine.h"
#include "../Game/BaseGame.h"
#include "../Graphics/Quad.h"
#include "../Util/Ref.h"
#include "../Graphics/Font.h"
#include "../Audio/Audio.h"
#include "../Graphics/Spritesheet.h"
#include "../Util/Timer.h"

using namespace JEngine;

class MyGame : public JEngine::BaseGame
{
private:
    Ref<Spritesheet> block;
    Ref<Font> font;
    Ref<Sound> sound;
    Ref<Timer> timer;
    const float speed = 25.0f;

public:
    MyGame()
        : BaseGame(1280, 720, "Test Game", false)
    {
        flags() << EnableAudio << EnableFonts;
        setResourceLocation("res");

        window().center();
        window().vsync(true);

        block = make_ref<Spritesheet>(100, 100, 100, 100, res("spritesheet.png"), 32);
        block->linearInterp(true);
        block->addCycle("walking", {0, 0}, {1, 0});
        block->addCycle("running", {0, 1}, {1, 1});
        block->setActiveCycle("running");

        timer = make_ref<Timer>(250, [&]() {
            block->next();
        }, true);

        font = make_ref<Font>(res("Roboto-Regular.ttf"), 18, &window());

        sound = make_ref<Sound>(res("Oblivious.mp3"));
        // Audio::playSound(*sound, 50, false);
    }

    virtual ~MyGame() {

    }

    virtual void update(float delta)
    {
        if (window().key('D'))
            block->translate(speed * delta, 0);
        if (window().key('A'))
            block->translate(-speed * delta, 0);
        if (window().key('S'))
            block->translate(0, speed * delta);
        if (window().key('W'))
            block->translate(0, -speed * delta);

        if (window().keyOnce('R')) {
            Animate::singleVar(0, 90, 750, Animation::Absolute, [&](float dx) {
                block->rotate(dx);
            });
        }

        if (window().keyOnce(KeySpace))
            block->setAngle(0);

        if (window().keyOnce(KeyTab)) {
            if (block->getActiveCycleName() == "running")
                block->setActiveCycle("walking");
            else
                block->setActiveCycle("running");
        }
    }

    virtual void render(Matrix4f screen)
    {
        window().clear(0, 128, 256);
        block->render(screen);

        std::string fps = "FPS: " + std::to_string(window().getFPS());
        font->render(5, font->height(fps) + 5, fps, {1, 1, 1});
    }
};

int main(int argc, char** argv)
{
    MyGame game;
    game.start();
    return 0;
}