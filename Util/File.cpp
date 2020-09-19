#include "File.h"

namespace JEngine {

    unsigned char* File::readBinary(const std::string& path, int* out_size)
    {
        FILE* file = fopen(path.c_str(), "rb");
        if (!file) {
            JERROR("(File) Could not load binary file '%s'", path.c_str());
            return nullptr;
        }

        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);

        auto* data = new unsigned char[size + 1];
        fread(data, 1, size, file);
        fclose(file);

        data[size] = '\0';
        if (out_size)
            *out_size = size;
        return data;
    }

}