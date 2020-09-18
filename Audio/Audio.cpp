#include "Audio.h"

namespace JEngine {

    ALCdevice* Audio::_device = nullptr;
    ALCcontext* Audio::_context = nullptr;
    std::vector<Sound> Audio::_sounds = std::vector<Sound>();
    std::queue<Audio::AudioQueueItem> Audio::_sound_queue = std::queue<Audio::AudioQueueItem>();
    bool Audio::_filters = false;
    ALuint Audio::_test_filter;
    bool Audio::_initialized = false;

    void Audio::initialize()
    {
        _device = alcOpenDevice(nullptr);
        if (!_device) {
            JERROR("(OpenAL) Could not initialize device");
            throw;
        }

        ALint attribs[4] = {0};
        if (alcIsExtensionPresent(_device, "ALC_EXT_EFX") == AL_TRUE) {
            _filters = true;
            attribs[0] = ALC_MAX_AUXILIARY_SENDS;
            attribs[1] = 4;
        }

        _context = alcCreateContext(_device, attribs);
        if (!alcMakeContextCurrent(_context)) {
            JERROR("(OpenAL) Could not make audio context current");
            throw;
        }

        // Generate test lowpass filter
        alGenFilters(1, &_test_filter);
        if (alGetError() == AL_NO_ERROR)
            JINFO("(OpenAL) Generated filter");
        else
            JERROR("(OpenAL) Filter generation failed");

        alFilteri(_test_filter, AL_FILTER_TYPE, AL_FILTER_LOWPASS);
        if (alGetError() != AL_NO_ERROR)
            JERROR("(OpenAL) Lowpass not supported");

        alFilterf(_test_filter, AL_LOWPASS_GAIN, 1.0f);
        alFilterf(_test_filter, AL_LOWPASS_GAINHF, 0.005f);

        _initialized = true;
        JINFO("(OpenAL) Context created");

        // Play the sounds that have been queued
        while (!_sound_queue.empty()) {
            auto[sound, vol, loop] = _sound_queue.front();
            playSound(sound, vol, loop);
            _sound_queue.pop();
        }
    }

    void Audio::playSound(Sound& sound, int vol, bool loop)
    {
        if (!_initialized) {
            JINFO("(OpenAL) Queueing sound for playback");
            _sound_queue.push({sound, vol, loop});
            return;
        }

        // Set audio source
        ALuint source;
        alGenSources((ALuint) 1, &source);
        sound.setALSource(source);

        // Set data in AL buffer
        alGenBuffers((ALuint) 1, &sound._al_buffer);
        alBufferData(sound._al_buffer, sound._data->alFormat(), sound._data->getData(),
                     sound._data->getDataSize(), sound._data->getSampleRate());

        // Push into list of currently playing sounds
        _sounds.push_back(sound);

        alSourcef(source, AL_PITCH, 1);
        alSourcef(source, AL_GAIN, vol / 100.0f);
        alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
        alSourcei(source, AL_BUFFER, sound.getALBuffer());

        JINFO("(OpenAL) Playing sound");
        alSourcePlay(source);
    }

    void Audio::audioLoop()
    {
        for (int i = 0; i < _sounds.size(); i++) {
            const Sound& sound = _sounds[i];
            ALint source_state;
            alGetSourcei(sound.getSource(), AL_SOURCE_STATE, &source_state);
            if (source_state == AL_STOPPED) {
                JINFO("(OpenAL) Cleaning up sound");
                ALuint source = sound.getSource();
                alDeleteSources(1, &source);
                _sounds.erase(_sounds.begin() + i);
            }
        }
    }

    void Audio::cleanup()
    {
        if (!_initialized)
            return;

        alcMakeContextCurrent(nullptr);
        alcDestroyContext(_context);
        alcCloseDevice(_device);
        JINFO("(OpenAL) Context destroyed");
    }

}