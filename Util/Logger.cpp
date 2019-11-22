#include "Logger.h"

namespace JEngine  {

    Logger::Logger(const std::string &name)
    : _name(name)
    {}

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
        std::cout << "[INFO] (" << _name << ") ";
        printf(msg, args);
        va_end(args);
    }

    void Logger::warn(const char *msg, ...) {
        va_list args;
        va_start(args, msg);
        std::cout << "[WARN] (" << _name << ") ";
        printf(msg, args);
        va_end(args);
    }

    void Logger::error(const char *msg, ...) {
        va_list args;
        va_start(args, msg);
        std::cout << "[ERROR] (" << _name << ") ";
        printf(msg, args);
        va_end(args);
    }

    void Logger::critical(const char *msg, ...) {
        va_list args;
        va_start(args, msg);
        std::cout << "[CRITICAL] (" << _name << ") ";
        printf(msg, args);
        va_end(args);
    }
    
    // TODO: move this
    Logger* Logger::engine = new Logger("JEngine");

}