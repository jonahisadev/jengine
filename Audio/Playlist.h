#pragma once

#include <vector>

#include "Audio.h"
#include "Sound.h"
#include "../Util/Ref.h"

namespace JEngine {

    class Playlist
    {
    public:
        enum LoopState {
            LoopNone,
            LoopPlaylist,
            LoopSound
        };

    private:
        std::vector<Sound> _sounds;
        LoopState _loop;
        int _index;
        int _volume;

    public:
        Playlist();
        virtual ~Playlist();

        LoopState getLoopState();
        void setLoopState(LoopState loop);

        void start();
        void next();
        void prev();
        void play();
        void pause();

        void addSound(Sound& sound);
        void addSound(Ref<Sound> sound);
    };

}