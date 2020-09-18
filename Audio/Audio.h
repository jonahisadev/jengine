#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include "Sound.h"
#include "../Util/Logger.h"

namespace JEngine {

    class Audio
    {
    private:
        struct AudioQueueItem
        {
            Sound& sound;
            int volume;
            bool loop;
        };

        static ALCdevice* _device;
        static ALCcontext* _context;
        static std::queue<AudioQueueItem> _sound_queue;
        static std::vector<Sound> _sounds;
        static bool _filters;
        static ALuint _test_filter;
        static bool _initialized;

    public:
        static void initialize();

        static void audioLoop();

        static void cleanup();

        static bool contextHasFilters()
        { return _filters; }

        static ALuint getFilter()
        { return _test_filter; }

        static void playSound(Sound& sound, int vol = 100, bool loop = false);
    };

#define LOAD_PROC(T, x) static T x = (T)alGetProcAddress(#x)

    LOAD_PROC(LPALGENEFFECTS, alGenEffects);
    LOAD_PROC(LPALGENAUXILIARYEFFECTSLOTS, alGenAuxiliaryEffectSlots);
    LOAD_PROC(LPALGENFILTERS, alGenFilters);
    LOAD_PROC(LPALFILTERI, alFilteri);
    LOAD_PROC(LPALFILTERF, alFilterf);

}