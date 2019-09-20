#include "Sound.h"

namespace JEngine {

    Sound::Sound(const char *path)
    {
        _data = new WaveData(path);
        std::cout << "OpenAL: Sound buffer size: " << (_data->getDataSize()) << std::endl;
        
        alGenBuffers((ALuint)1, &_al_buffer);
        alBufferData(_al_buffer, _data->alFormat(), _data->getData(), _data->getDataSize(), _data->getSampleRate());
    }

    Sound::~Sound() {
        alDeleteBuffers((ALuint)1, &_al_buffer);
        delete _data;
    }

}