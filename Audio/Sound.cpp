#include "Sound.h"
#include "Audio.h"

#include <memory>

namespace JEngine {

    Sound::Sound(const std::string& path)
    {
        const std::string end = path.substr(path.length() - 4, 4);
        if (end == ".wav")
            _data = make_ref<WaveData>(path);
        else if (end == ".mp3")
            _data = make_ref<MP3Data>(path);
        else {
            JERROR("(OpenAL) Invalid file format");
            throw;
        }
        JINFO("(OpenAL) Sound buffer size: %d bytes", _data->getBufferSize());
    }

    Sound::~Sound()
    {
        alDeleteBuffers((ALuint) 1, &_al_buffer);
    }

    void Sound::pause()
    {
        alSourcePause(_al_source);
    }

    void Sound::play()
    {
        alSourcePlay(_al_source);
    }

    void Sound::togglePlayback()
    {
        ALint source_state;
        alGetSourcei(_al_source, AL_SOURCE_STATE, &source_state);
        if (source_state == AL_PLAYING)
            pause();
        else if (source_state == AL_PAUSED)
            play();
    }

    void Sound::stop()
    {
        alSourceStop(_al_source);
    }

    void Sound::applyFilter(bool filter)
    {
        if (Audio::contextHasFilters()) {
            alSourcei(_al_source, AL_DIRECT_FILTER, filter ? Audio::getFilter() : AL_FILTER_NULL);
            if (alGetError() == AL_NO_ERROR)
                JINFO("(OpenAL) Applied filter");
        } else {
            JERROR("(OpenAL) Filter not supported");
        }
    }

}