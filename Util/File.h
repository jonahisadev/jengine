#pragma once

#include <iostream>
#include <cstdio>

namespace JEngine {
    
    class File {
    public:
        static unsigned char* readBinary(const char* path);
    };
    
}