#pragma once

#include "AudioData.h"
#include "WaveData.h"
#include "Mp3Data.h"
#include "../Util/Ref.h"

namespace JEngine {

    class Sound
    {
    private:
        Ref<AudioData> _data;
        ALuint _al_buffer;
        ALuint _al_source;

    public:
        Sound(const std::string& path);
        ~Sound();

        void pause();
        void play();
        void togglePlayback();
        void stop();

        void applyFilter(bool filter);

        inline ALuint getALBuffer() const { return _al_buffer; }
        inline ALuint* getALBufferPtr() { return &_al_buffer; }
        void setALSource(ALuint source) { _al_source = source; }
        inline ALuint getSource() const { return _al_source; }
        inline AudioData* data() { return _data.get(); }
    };

}