#include "Game.h"


namespace JEngine {

    Bitmask Game::_flags;

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

}