#pragma once

#include "../Audio/Audio.h"
#include "../Graphics/Font.h"
#include "../Util/Bitmask.h"

namespace JEngine {

    class Game {
    public:
        enum GameFlags {
            EnableAudio,
            EnableFonts
        };
        
    private:
        static Bitmask _flags;
        
    public:
        static inline Bitmask& flags() { return _flags; }
        
        static void init();
        static void cleanup();
    };

}