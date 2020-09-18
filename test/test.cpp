#include "../JEngine.h"
#include "../Game/BaseGame.h"
#include "../Graphics/Quad.h"
#include "../Graphics/Font.h"
#include "../Audio/Audio.h"

using namespace JEngine;

class MyGame : public JEngine::BaseGame
{
private:
    TexturedQuad* block;
    Font* font;
    Sound* sound;

    const float speed = 25.0f;

public:
    MyGame()
        : BaseGame(1280, 720, "Test Game", false)
    {
        flags() << EnableAudio << EnableFonts;
        setResourceLocation("res");

        window().center();
        window().vsync(true);

        block = new TexturedQuad(100, 100, 100, 100, res("coyote.png"));
        font = new Font(res("Roboto-Regular.ttf"), 18, &window());

        sound = new Sound(res("daniel.wav"));
        // Audio::playSound(*sound, 50, true);
    }

    virtual ~MyGame() {
        delete font;
        delete sound;
        delete block;
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

        if (window().key('R'))
            block->rotate(speed * delta);
    }

    virtual void render(Matrix4f screen)
    {
        window().clear(0, 128, 256);
        block->render(screen);

        std::string fps = "FPS: " + std::to_string(window().getFPS());
        font->render(5, 20, fps, {1, 1, 1});
    }
};

int main(int argc, char** argv)
{
    MyGame game;
    game.start();
    return 0;
}