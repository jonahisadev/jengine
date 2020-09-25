#include "Playlist.h"

namespace JEngine {

    Playlist::Playlist()
        : _index(0), _loop(LoopNone), _volume(100)
    {}

    Playlist::~Playlist()
    {}

    Playlist::LoopState Playlist::getLoopState()
    {
        return _loop;
    }

    void Playlist::setLoopState(Playlist::LoopState loop)
    {
        _loop = loop;
    }

    void Playlist::start()
    {
        Audio::playSound(_sounds.at(_index), _volume);
    }

    void Playlist::next()
    {
        // Stop current sound
        _sounds[_index].stop();

        // If we're looping the sound, start over
        if (_loop == LoopSound) {
            Audio::playSound(_sounds.at(_index), _volume);
            _sounds[_index].play();
            return;
        }

        // We're at the end of the playlist
        if (_index + 1 >= _sounds.size()) {

            // Start over playlist
            if (_loop == LoopPlaylist) {
                _index = 0;
                Audio::playSound(_sounds.at(_index), _volume);
            }

            // Otherwise, get out
            return;
        }

        // Play the sound that's next
        Audio::playSound(_sounds.at(++_index), _volume);
    }

    void Playlist::prev()
    {
        // Stop current sound
        _sounds[_index].stop();

        // If we're looping the sound, start over
        if (_loop == LoopSound) {
            Audio::playSound(_sounds.at(_index), _volume);
            _sounds[_index].play();
            return;
        }

        // We're at the end of the playlist
        if (_index - 1 <= 0) {

            // Go to end of playlist
            if (_loop == LoopPlaylist) {
                _index = _sounds.size() - 1;
                Audio::playSound(_sounds.at(_index), _volume);
            }

            // Otherwise, get out
            return;
        }

        // Play the sound that's next
        Audio::playSound(_sounds.at(--_index), _volume);
    }

    void Playlist::play()
    {
        _sounds[_index].play();
    }

    void Playlist::pause()
    {
        _sounds[_index].pause();
    }

    void Playlist::addSound(Sound& sound)
    {
        _sounds.push_back(sound);
    }

    void Playlist::addSound(Ref<Sound> sound)
    {
        _sounds.push_back(*sound);
    }

}