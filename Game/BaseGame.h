#pragma once

#include <string>
#include "../Util/Bitmask.h"
#include "../Graphics/Display.h"

namespace JEngine {

    class BaseGame
    {
    protected:
        enum GameFlags {
            EnableAudio,
            EnableFonts
        };

    private:
        Display _display;
        Bitmask _flags;
        std::string _res;

        void init();

    public:
        BaseGame(int width, int height, const std::string& title = "JEngine", bool resize = false);
        virtual ~BaseGame();

        virtual void update(float delta) = 0;
        virtual void render(Matrix4f screen) = 0;

        void start();

    protected:
        inline Bitmask& flags() { return _flags; }
        Display& window() { return _display; }

        void setResourceLocation(const std::string& path);
        std::string res(const std::string& path);

        friend class Display;
    };

}