#pragma once

#include <vector>
#include <functional>

namespace JEngine {

    class Timer
    {
    private:
        int _ms;
        int _passed_ms;
        bool _loop;
        bool _finished;
        std::function<void()> _callback;

        static std::vector<Timer*> g_timers;

        void elapse(int ms);
        bool isFinished() const { return _finished; }

    public:
        Timer();
        Timer(int ms, std::function<void()> callback, bool loop = false);
        virtual ~Timer();

        void set(int ms, std::function<void()> callback, bool loop = false);

        static void run(float delta);
    };

}