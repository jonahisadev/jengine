#pragma once

#include <iostream>
#include <cstdio>

#include "../Util/Logger.h"

namespace JEngine {
    
    class File {
    public:
        static unsigned char* readBinary(const char* path);
    };
    
}