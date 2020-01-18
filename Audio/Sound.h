#pragma once

#include "WaveData.h"

namespace JEngine {

    class Sound {
    private:
        WaveData* _data;
        ALuint _al_buffer;
        ALuint _al_source;
        
    public:
        Sound(const char* path);
        ~Sound();
        
        void pause();
        void play();
        void togglePlayback();
        void stop();
        
        void applyFilter(bool filter);
        
        inline ALuint getALBuffer() const { return _al_buffer; }
        
        void setALSource(ALuint source) { _al_source = source; }
        inline ALuint getSource() const { return _al_source; }
    };

}