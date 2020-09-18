#include "BaseGame.h"
#include "../Audio/Audio.h"
#include "../Graphics/Font.h"

namespace JEngine {

    BaseGame::BaseGame(int width, int height, const std::string& title, bool resize)
            : _display(width, height, title.c_str(), resize)
    {}

    BaseGame::~BaseGame()
    {
        if (_flags[EnableAudio])
            Audio::cleanup();
        if (_flags[EnableFonts])
            Font::cleanup();
    }

    void BaseGame::init()
    {
        if (_flags[EnableAudio])
            Audio::initialize();
    }

    void BaseGame::setResourceLocation(const std::string& path)
    {
        _res = path;
        if (_res.substr(_res.length() - 1) != "/")
            _res += "/";
    }

    std::string BaseGame::res(const std::string& path)
    {
        return std::string(_res + path);
    }

    void BaseGame::start()
    {
        auto update_fn = [this](float delta) {
            this->update(delta);
        };

        auto render_fn = [this](Matrix4f screen) {
            this->render(screen);
        };

        _display.run(this, render_fn, update_fn);
    }

}