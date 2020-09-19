#pragma once

#include <AL/al.h>
#include "AudioData.h"
#include "../Util/File.h"
#include "../Util/Logger.h"

namespace JEngine {

    class WaveData : public AudioData
    {
    private:
        unsigned int _channels;
        unsigned int _bitrate;
        unsigned int _sample_rate;
        unsigned int _raw_size;
        unsigned char* _data;
        
    public:
        WaveData(const std::string& path);
        ~WaveData();
        
        ALenum alFormat() override;
        
        unsigned int getChannels() override { return _channels; }
        unsigned int getBitrate() override { return _bitrate; }
        unsigned int getSampleRate() override { return _sample_rate; }
        void* getBuffer() override { return _data; }
        unsigned int getBufferSize() override { return _raw_size; }
    };
    
}