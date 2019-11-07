#include "TexturedMesh.h"

namespace JEngine {

    TexturedMesh::TexturedMesh(float *buffer, const Vector3f &color, int *els, int vCount, int lCount, const char *path)
    : Mesh(buffer, {1, 1, 1}, els, vCount, lCount), _tex(0)
    {
        delete _shader;
        _shader = new Shader(Shader::DefaultTextureVertexShader, Shader::DefaultTextureFragmentShader);

        int width, height, channels;
        unsigned char* pixel_data = SOIL_load_image(path, &width, &height, &channels, SOIL_LOAD_AUTO);
        _img_width = width;
        _img_height = height;

        // Generate texture
        glGenTextures(1, &_tex);
        glBindTexture(GL_TEXTURE_2D, _tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Bind buffers
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        // Texture wrapping
        glBindTexture(GL_TEXTURE_2D, _tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Turn off linear interpolation by default
        linearInterp(false);

        // Enable UV coords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    TexturedMesh::~TexturedMesh() {
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        glDeleteVertexArrays(1, &_vao);
    }
    
    void TexturedMesh::linearInterp(bool state) {
        if (state) {
            glBindTexture(GL_TEXTURE_2D, _tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
        } else {
            glBindTexture(GL_TEXTURE_2D, _tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    void TexturedMesh::render(Matrix4f screen) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _tex);

        _shader->use();
        _shader->setMat4("model", _model);
        _shader->setMat4("screen", screen);
        _shader->setVec3("color", _color);
        _shader->setInt("tex", 0);
        
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _list_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        _shader->stop();
    }

    void TexturedMesh::setUV(const float *uv) {
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        for (int i = 0; i < _vertex_count; i++) {
            float coord[2];
            coord[0] = uv[(i * 2) + 0];
            coord[1] = uv[(i * 2) + 1];
            glBufferSubData(GL_ARRAY_BUFFER, ((i * 4) + 2) * sizeof(float), 2 * sizeof(float), coord);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

}