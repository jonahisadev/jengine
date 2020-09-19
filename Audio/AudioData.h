#pragma once

#include <AL/al.h>

namespace JEngine {

    class AudioData
    {
    public:
        virtual ~AudioData() {}

        virtual ALenum alFormat() = 0;
        virtual unsigned int getChannels() = 0;
        virtual unsigned int getBitrate() = 0;
        virtual unsigned int getSampleRate() = 0;
        virtual void* getBuffer() = 0;
        virtual unsigned int getBufferSize() = 0;
    };

}