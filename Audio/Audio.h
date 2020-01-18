#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <vector>
#include <algorithm>

#include "Sound.h"
#include "../Util/Logger.h"

namespace JEngine {

    class Audio {
    private:
        static ALCdevice *_device;
        static ALCcontext* _context;
        static std::vector<Sound*> _sounds;
        
    public:
        static void initialize();
        static void audioLoop();
        static void cleanup();
        
        static void playSound(Sound& sound, int vol = 100, bool loop = false);
    };

}