#include "File.h"

namespace JEngine {

    unsigned char* File::readBinary(const char *path) {
        FILE* file = fopen(path, "rb");
        if (!file) {
            JERROR("(File) Could not load binary file '%s'", path);
            return nullptr;
        }
        
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        auto* data = new unsigned char[size+1];
        fread(data, 1, size, file);
        fclose(file);
        
        data[size] = '\0';
        return data;
    }

}