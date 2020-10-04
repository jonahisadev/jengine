#include "Timer.h"

#include <iostream>

namespace JEngine {

    std::vector<Timer*> Timer::g_timers = std::vector<Timer*>();

    Timer::Timer()
        : _ms(0), _passed_ms(0), _callback(), _loop(false), _finished(false)
    {}

    Timer::Timer(int ms, std::function<void()> callback, bool loop)
        : _ms(ms), _passed_ms(0), _callback(callback), _loop(loop), _finished(false)
    {
        g_timers.push_back(this);
    }

    Timer::~Timer()
    {}

    void Timer::set(int ms, std::function<void()> callback, bool loop)
    {
        _ms = ms;
        _callback = std::move(callback);
        _loop = loop;
        g_timers.push_back(this);
    }

    void Timer::elapse(int ms)
    {
        _passed_ms += ms;
        if (_passed_ms >= _ms) {
            _callback();
            if (_loop)
                _passed_ms = 0;
            else
                _finished = true;
        }
    }

    void Timer::run(float delta)
    {
        int ms = int(delta * 100);

        auto it = g_timers.begin();
        while (it != g_timers.end()) {
            (*it)->elapse(ms);
            if ((*it)->isFinished())
                it = g_timers.erase(it);
            else
                ++it;
        }
    }

}