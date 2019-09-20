#pragma once

namespace JEngine {

    class Bitmask {
    private:
        unsigned int _flags;
        
    public:
        Bitmask() : _flags(0) {}
        
        void set(int index, int value);
        unsigned int get(int index);
        inline void clear() { _flags = 0; }
        
        unsigned int operator[](int index);
        Bitmask& operator<<(int index);
    };

}