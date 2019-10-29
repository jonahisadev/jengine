#include "TexturedMesh.h"

namespace JEngine {

    TexturedMesh::TexturedMesh(float* pos, float* color, int* els, int vCount, int lCount, const char* path)
    : Mesh(pos, {1, 1, 1}, els, vCount, lCount)
    {
        int width, height, channels;
        unsigned char* pixel_data = SOIL_load_image(path, &width, &height, &channels, SOIL_LOAD_AUTO);
        _img_width = width;
        _img_height = height;
        
        _buffers[BufferTexture] = SOIL_create_OGL_texture(
            pixel_data, 
            width, height, channels, 
            0,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
        
        // TODO: For smaller images, this will create a weird border
        glBindTexture(GL_TEXTURE_2D, _buffers[BufferTexture]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        // Turn off linear interpolation by default
        linearInterp(false);
        
        float coords[] = {
            0, 0,
            1, 0,
            1, 1,
            0, 1
        };
        
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferCoords]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, coords, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        _textured = true;
    }

    TexturedMesh::~TexturedMesh() {
        glDeleteBuffers(BufferCount, _buffers);
    }

    void TexturedMesh::setUV(float *uv) {
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferCoords]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 2 * _vertex_count, uv);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void TexturedMesh::linearInterp(bool state) {
        if (state) {
            glBindTexture(GL_TEXTURE_2D, _buffers[BufferTexture]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
        } else {
            glBindTexture(GL_TEXTURE_2D, _buffers[BufferTexture]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

}