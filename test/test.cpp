#include "../JEngine.h"
#include "../Game/BaseGame.h"
#include "../Graphics/BasicQuad.h"
#include "../Util/Ref.h"
#include "../Graphics/Font.h"
#include "../Audio/Audio.h"
#include "../Graphics/Spritesheet.h"
#include "../Util/Timer.h"
#include "../Audio/Playlist.h"
#include "../Graphics/Sprite.h"

using namespace JEngine;

class MyGame : public JEngine::BaseGame
{
private:
    Ref<Spritesheet> block;
    Ref<Font> font;
    Ref<Playlist> playlist;
    Ref<Timer> timer;
    Ref<Sprite> a, b;
    const float speed = 25.0f;

public:
    MyGame()
        : BaseGame(1280, 720, "Test Game", false)
    {
        flags() << EnableAudio << EnableFonts;
        setResourceLocation("res");

        window().center();
        window().vsync(true);

        block = make_ref<Spritesheet>(0, 0, 0, 0, res("spritesheet.png"), 32);
        block->linearInterp(true);
        a = block->createSprite(100, 100, 100, 100, {1, 1});
        b = block->createSprite(300, 200, 100, 100, {0, 0});

        font = make_ref<Font>(res("Roboto-Regular.ttf"), 18, &window());

        playlist = make_ref<Playlist>();
        playlist->addSound(make_ref<Sound>(res("daniel.wav")));
        playlist->addSound(make_ref<Sound>(res("Oblivious.mp3")));
        playlist->setLoopState(Playlist::LoopPlaylist);
        playlist->start();
    }

    virtual ~MyGame() {

    }

    virtual void update(float delta)
    {
        if (window().key('D'))
            a->translate(speed * delta, 0);
        if (window().key('A'))
            a->translate(-speed * delta, 0);
        if (window().key('S'))
            a->translate(0, speed * delta);
        if (window().key('W'))
            a->translate(0, -speed * delta);

        if (window().keyOnce('R')) {
            Animate::singleVar(0, 90, 750, Animation::Absolute, [&](float dx) {
                a->rotate(dx);
                // b->rotate(dx);
            });
        }

        // if (window().keyOnce(KeyTab)) {
        //     if (block->getActiveCycleName() == "running")
        //         block->setActiveCycle("walking");
        //     else
        //         block->setActiveCycle("running");
        // }
    }

    virtual void render(Matrix4f screen)
    {
        window().clear(0, 128, 256);
        // block->render(screen);

        a->render(screen);
        b->render(screen);

        std::string fps = "FPS: " + std::to_string(window().getFPS());
        font->render(5, font->height(fps) + 5, fps, {1, 1, 1});
        std::string coords = "X: " + std::to_string((int)a->x()) 
            + ", Y: " + std::to_string((int)a->y());
        font->render(5, 40, coords, {1, 1, 1});
    }
};

int main(int argc, char** argv)
{
    MyGame game;
    game.start();
    return 0;
}