#include "Mesh.h"

namespace JEngine {

    Mesh::Mesh(float *pos, float *color, int *els, int vCount, int lCount) 
    : _vertex_count(vCount), _list_count(lCount)
    {
        glGenBuffers(BufferCount, _buffers);
        
        setPosition(pos);
        setColor(color);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[BufferIndex]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * _list_count, els, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Mesh::~Mesh() {
        glDeleteBuffers(BufferCount, _buffers);
    }

    void Mesh::setPosition(float *pos) {
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferPosition]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * _vertex_count, pos, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Mesh::setColor(float *color) {
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferColor]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * _vertex_count, color, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Mesh::render() {
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferPosition]);
        glVertexPointer(2, GL_FLOAT, 0, 0);
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferColor]);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glEnableClientState(GL_COLOR_ARRAY);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[BufferIndex]);
        glDrawElements(GL_TRIANGLES, _list_count, GL_UNSIGNED_INT, 0);
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}