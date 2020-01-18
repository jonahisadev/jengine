#include "Audio.h"

namespace JEngine {

    ALCdevice* Audio::_device = nullptr;
    ALCcontext* Audio::_context = nullptr;
    std::vector<Sound*> Audio::_sounds = std::vector<Sound*>();
    
    void Audio::initialize() {
        _device = alcOpenDevice(nullptr);
        if (!_device) {
            JERROR("(OpenAL) Could not initialize device");
            throw;
        }
        
        _context = alcCreateContext(_device, nullptr);
        if (!alcMakeContextCurrent(_context)) {
            JERROR("(OpenAL) Could not make audio context current");
            throw;
        }

        JINFO("(OpenAL) Context created");
    }

    void Audio::playSound(Sound &sound, int vol, bool loop) {
        ALuint source;
        alGenSources((ALuint)1, &source);
        sound.setALSource(source);
        _sounds.push_back(&sound);
        
        alSourcef(source, AL_PITCH, 1);
        alSourcef(source, AL_GAIN, vol / 100.0f);
        alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
        alSourcei(source, AL_BUFFER, sound.getALBuffer());
        
        JINFO("(OpenAL) Playing sound");
        alSourcePlay(source);
    }

    void Audio::audioLoop() {
        for (int i = 0; i < _sounds.size(); i++) {
            const Sound* sound = _sounds[i];
            ALint source_state;
            alGetSourcei(sound->getSource(), AL_SOURCE_STATE, &source_state);
            if (source_state != AL_PLAYING) {
                JINFO("(OpenAL) Cleaning up sound");
                ALuint source = sound->getSource();
                alDeleteSources(1, &source);
                _sounds.erase(_sounds.begin() + i);
            }
        }
    }

    void Audio::cleanup() {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(_context);
        alcCloseDevice(_device);
        JINFO("(OpenAL) Context destroyed");
    }

}