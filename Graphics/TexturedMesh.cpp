#include "TexturedMesh.h"

namespace JEngine {

    TexturedMesh::TexturedMesh(float* pos, float* color, int* els, int vCount, int lCount, const char* path)
    : Mesh(pos, color, els, vCount, lCount)
    {
        _buffers[BufferTexture] = SOIL_load_OGL_texture(
            path,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
        
        glBindTexture(GL_TEXTURE_2D, _buffers[BufferTexture]);
        // FIXME: The texture parameters assume "retro" graphics. Have this as an option.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        float coords[] = {
            0, 0,
            1, 0,
            1, 1,
            0, 1
        };
        
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferCoords]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, coords, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        _textured = true;
    }

    TexturedMesh::~TexturedMesh() {
        glDeleteBuffers(BufferCount, _buffers);
    }

}