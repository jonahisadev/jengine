#include "Mesh.h"

namespace JEngine {

//    Mesh::Mesh(float *pos, float *color, int *els, int vCount, int lCount) 
//    : _vertex_count(vCount), _list_count(lCount)
//    {
//        glGenBuffers(BufferCount, _buffers);
//
//        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferPosition]);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * _vertex_count, pos, GL_DYNAMIC_DRAW);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferColor]);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * _vertex_count, color, GL_STATIC_DRAW);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[BufferIndex]);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * _list_count, els, GL_STATIC_DRAW);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    }

    Mesh::Mesh(float *pos, float *color, int *els, int vCount, int lCount)
    : _shader(Shader())
    {
        _list_count = lCount;
        
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ebo);
        
        glBindVertexArray(_vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, vCount * 2 * sizeof(float), pos, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, lCount * sizeof(int), els, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Mesh::~Mesh() {
//        glDeleteBuffers(BufferCount, _buffers);
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
    }

    void Mesh::setPosition(float *pos) {
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferPosition]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 2 * _vertex_count, pos);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Mesh::setColor(float *color) {
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferColor]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * _vertex_count, color);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

//    void Mesh::render() {
//        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferPosition]);
//        glVertexPointer(2, GL_FLOAT, 0, 0);
//        glEnableClientState(GL_VERTEX_ARRAY);
//        
//        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferColor]);
//        glColorPointer(3, GL_FLOAT, 0, 0);
//        glEnableClientState(GL_COLOR_ARRAY);
//        
//        // Textures
//        if (_textured) {
//            glBindTexture(GL_TEXTURE_2D, _buffers[BufferTexture]);
//            glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferCoords]);
//            glTexCoordPointer(2, GL_FLOAT, 0, 0);
//            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//        }
//        
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[BufferIndex]);
//        glDrawElements(GL_TRIANGLES, _list_count, GL_UNSIGNED_INT, 0);
//        
//        glDisableClientState(GL_VERTEX_ARRAY);
//        glDisableClientState(GL_COLOR_ARRAY);
//        
//        if (_textured) {
//            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }
//        
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    }

    void Mesh::render() {
        // TODO: Move this to the Mesh
        glm::mat4 model = glm::mat4(1.0f);
        
        // TODO: Move this to a Scene
        glm::mat4 view = glm::mat4(1.0f);
        
        // TODO: Move this to the Display
        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

        _shader.use();
        _shader.setMat4("view", view);
        _shader.setMat4("projection", projection);
        _shader.setMat4("model", model);
        _shader.setVec3("color", 1, 1, 1);
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _list_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        _shader.stop();
    }

}