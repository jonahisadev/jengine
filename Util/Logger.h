#pragma once

#include <iostream>
#include <iomanip>
#include <cstdarg>

namespace JEngine {

    class Logger
    {
    private:
        std::string _name;
        static void printf(const char* str, va_list args);

    public:
        static Logger* engine;

        Logger(const std::string& name);

        void info(const char* msg, ...);
        void warn(const char* msg, ...);
        void error(const char* msg, ...);
        void critical(const char* msg, ...);
    };

}

#define VA_ARGS(...) , ##__VA_ARGS__

#define JINFO(x, ...) JEngine::Logger::engine->info(x VA_ARGS(__VA_ARGS__))
#define JWARN(x, ...) JEngine::Logger::engine->warn(x VA_ARGS(__VA_ARGS__))
#define JERROR(x, ...) JEngine::Logger::engine->error(x VA_ARGS(__VA_ARGS__))
#define JCRITICAL(x, ...) JEngine::Logger->critical(x VA_ARGS(__VA_ARGS__))

#ifdef JENGINE_RELEASE
#define JINFO(x, ...)
#define JWARN(x, ...)
#define JERROR(x, ...)
#define JCRITICAL(x, ...)
#endif