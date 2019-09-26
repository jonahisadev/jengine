#pragma once

#include <iostream>
#include <iomanip>
#include <cstdarg>

namespace JEngine {

    class Logger {
    private:
        static void printf(const char* str, va_list args);

    public:
        static void info(const char* msg, ...);
        static void warn(const char* msg, ...);
        static void error(const char* msg, ...);
        static void critical(const char* msg, ...);
    };

}

#define VA_ARGS(...) , ##__VA_ARGS__

#define JINFO(x, ...) JEngine::Logger::info(x VA_ARGS(__VA_ARGS__))
#define JWARN(x, ...) JEngine::Logger::warn(x VA_ARGS(__VA_ARGS__))
#define JERROR(x, ...) JEngine::Logger::error(x VA_ARGS(__VA_ARGS__))
#define JCRITICAL(x, ...) JEngine::Logger::critical(x VA_ARGS(__VA_ARGS__))

#ifdef JENGINE_RELEASE
#define JINFO(x, ...)
#define JWARN(x, ...)
#define JERROR(x, ...)
#define JCRITICAL(x, ...)
#endif