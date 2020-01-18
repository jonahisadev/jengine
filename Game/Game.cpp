#include "Game.h"

#include <utility>

namespace JEngine {

    Bitmask Game::_flags;
    std::string Game::_res;

    void Game::init() {
        if (_flags[EnableAudio])
            Audio::initialize();
    }

    void Game::cleanup() {
        if (_flags[EnableAudio])
            Audio::cleanup();
        if (_flags[EnableFonts])
            Font::cleanup();
    }

    void Game::setResourceLocation(const std::string& path) {
        _res = path;
        if (_res.substr(_res.length() - 1) != "/")
            _res += "/";
    }

    std::string Game::resource(const std::string& path) {
        return std::string(_res + path);
    }

}