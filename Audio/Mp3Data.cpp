#include "Mp3Data.h"

#define MINIMP3_ONLY_MP3
#define MINIMP3_IMPLEMENTATION
#include <minimp3/minimp3.h>
#include <minimp3/minimp3_ex.h>

namespace JEngine {

    MP3Data::MP3Data(const std::string& path)
    {
        mp3dec_init(&_decoder);
        JINFO("(MP3) Decoding MP3...");
        if (mp3dec_load(&_decoder, path.c_str(), &_info, nullptr, nullptr)) {
            JERROR("(MP3) There was an error loading this MP3 file");
            throw;
        }

        JINFO("(MP3) Audio decoded");
    }

    MP3Data::~MP3Data()
    {
        JINFO("(MP3) Freeing buffer");
        free(_info.buffer);
    }

    ALenum MP3Data::alFormat()
    {
        if (_info.channels == 2)
            return AL_FORMAT_STEREO16;
        return AL_FORMAT_MONO16;
    }

}