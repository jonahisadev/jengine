#pragma once

#include <iostream>
#include <string>
#include <minimp3/minimp3_ex.h>
#include "../Util/Logger.h"

#include "AudioData.h"

namespace JEngine {

    class MP3Data : public AudioData
    {
    private:
        mp3dec_t _decoder;
        mp3dec_file_info_t _info;

    public:
        explicit MP3Data(const std::string& path);
        ~MP3Data() override;

        ALenum alFormat() override;

        unsigned int getChannels() override { return _info.channels; }
        unsigned int getBitrate() override { return _info.avg_bitrate_kbps; }
        unsigned int getSampleRate() override { return _info.hz; }
        void* getBuffer() override { return _info.buffer; }
        unsigned int getBufferSize() override { return _info.samples * sizeof(mp3d_sample_t); }
    };

}