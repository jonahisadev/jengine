#include "WaveData.h"

namespace JEngine {

    WaveData::WaveData(const char *path) {
        unsigned char* data = File::readBinary(path);
        
        // ChunkID
        if (data[0] != 'R' ||
            data[1] != 'I' ||
            data[2] != 'F' ||
            data[3] != 'F')
        {
            std::cerr << "WaveData: Incorrect ChunkID" << std::endl;
            throw;
        }
        
        // Channels
        _channels = data[22] | (data[23] << 8);
        
        // Bitrate
        _bitrate = data[34] | (data[35] << 8);
        
        // Sample Rate
        _sample_rate = data[24] | (data[25] << 8) | (data[26] << 16) | (data[27] << 24);
        
        // Data size
        _raw_size = data[40] | (data[41] << 8) | (data[42] << 16) | (data[43] << 24);
        
        std::cout << "OpenAL: Sound loaded = (" << _channels << ", " << _bitrate << ", " << _sample_rate
                << ", " << _raw_size << ")" << std::endl;
        
        // Allocate raw data
        _data = new unsigned char[_raw_size];
        
        // Copy data
        for (int i = 0; i < _raw_size; i++) {
            _data[i] = data[i + 44];
        }

        delete[] data;
    }

    WaveData::~WaveData() {
        delete _data;
    }

    ALenum WaveData::alFormat() {
        bool stereo = (_channels > 1);
        
        switch (_bitrate) {
            case 8:
                if (stereo)
                    return AL_FORMAT_STEREO8;
                return AL_FORMAT_MONO8;
            case 16:
                if (stereo)
                    return AL_FORMAT_STEREO16;
                return AL_FORMAT_MONO16;
            default:
                return -1;
        }
    }

}