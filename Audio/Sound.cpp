#include "Sound.h"

namespace JEngine {

    Sound::Sound(const char *path)
    {
        _data = new WaveData(path);
        JINFO("(OpenAL) Sound buffer size: %d", _data->getDataSize());        

        alGenBuffers((ALuint)1, &_al_buffer);
        alBufferData(_al_buffer, _data->alFormat(), _data->getData(), _data->getDataSize(), _data->getSampleRate());
    }

    Sound::~Sound() {
        alDeleteBuffers((ALuint)1, &_al_buffer);
        delete _data;
    }

}