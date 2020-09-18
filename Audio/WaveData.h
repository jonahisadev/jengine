#pragma once

#include <AL/al.h>
#include "../Util/File.h"
#include "../Util/Logger.h"

namespace JEngine {

    class WaveData
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
        
        ALenum alFormat();
        
        inline unsigned int getChannels() const { return _channels; }
        inline unsigned int getBitrate() const { return _bitrate; }
        inline unsigned int getSampleRate() const { return _sample_rate; }
        inline unsigned char* getData() const { return _data; }
        inline unsigned int getDataSize() const { return _raw_size; }
    };
    
}