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
        static std::string _res;
        
    public:
        static inline Bitmask& flags() { return _flags; }
        
        static void init();
        static void cleanup();
        
        static void setResourceLocation(const std::string& path);
        static std::string resource(const std::string& path);
    };

}