#include "Logger.h"

namespace JEngine  {

    void Logger::printf(const char *str, va_list args) {
        while (*str != '\0') {
            if (*str != '%')
                std::cout << *str;
            else {
                ++str;
                switch (*str) {
                    case 'd': {
                        int x = va_arg(args, int);
                        std::cout << x;
                        break;
                    }
                    case 'f': {
                        double x = va_arg(args, double);
                        std::cout << std::setprecision(4) << x;
                        break;
                    }
                    case 'x': {
                        int x = va_arg(args, int);
                        std::cout << std::hex << x;
                        break;
                    }
                    case 's': {
                        const char* x = va_arg(args, char*);
                        std::cout << x;
                    }
                    default: {
                        // Nothing
                    }
                }
            }
            ++str;
        }

        std::cout << std::endl;
    }

    void Logger::info(const char* msg, ...) {
        va_list args;
        va_start(args, msg);
        std::cout << "[JEngine::INFO] ";
        printf(msg, args);
        va_end(args);
    }

    void Logger::warn(const char *msg, ...) {
        va_list args;
        va_start(args, msg);
        std::cout << "[JEngine::WARN] ";
        printf(msg, args);
        va_end(args);
    }

    void Logger::error(const char *msg, ...) {
        va_list args;
        va_start(args, msg);
        std::cout << "[JEngine::ERROR] ";
        printf(msg, args);
        va_end(args);
    }

    void Logger::critical(const char *msg, ...) {
        va_list args;
        va_start(args, msg);
        std::cout << "[JEngine::CRITICAL] ";
        printf(msg, args);
        va_end(args);
    }

}