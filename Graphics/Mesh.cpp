#include "Mesh.h"

namespace JEngine {

    Mesh::Mesh(float *pos, const Vector3f& color, int *els, int vCount, int lCount)
    : _shader(Shader()), _list_count(lCount), _vertex_count(vCount), _color(color),
        _model(glm::mat4(1.0f))
    {
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
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
    }

    void Mesh::setPosition(const Vector2f &pos) {
        _model[3][0] = pos.x();
        _model[3][1] = pos.y();
    }

    void Mesh::setColor(const Vector3f& color) {
        _color = color;
    }

    void Mesh::translate(const Vector2f &pos) {
        _model = glm::translate(_model, glm::vec3(pos.x(), pos.y(), 0));
    }

    void Mesh::rotate(float dr) {
        _model = glm::rotate(_model, glm::radians(dr), glm::vec3(0, 0, 1));
    }

    void Mesh::render(Matrix4f screen) {
        _shader.use();
        _shader.setMat4("model", _model);
        _shader.setMat4("screen", screen);
        _shader.setVec3("color", _color);
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _list_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        _shader.stop();
    }

}