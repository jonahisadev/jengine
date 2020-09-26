#include "Mesh.h"
#include "TexturedMesh.h"

namespace JEngine {

    Mesh::Mesh(float* buffer, const Vector3f& color, int* els, int vCount, int lCount)
            : _shader(new Shader()), _list_count(lCount), _vertex_count(vCount), _color(color),
            _model(glm::mat4(1.0f))
    {
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ebo);

        glBindVertexArray(_vao);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, vCount * 4 * sizeof(float), buffer, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, lCount * sizeof(int), els, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        glDeleteVertexArrays(1, &_vao);
    }

    void Mesh::setPosition(const Vector2f& pos)
    {
        _model[3][0] = pos.x();
        _model[3][1] = pos.y();
    }

    void Mesh::setColor(const Vector3f& color)
    {
        _color = color;
    }

    void Mesh::translate(const Vector2f& pos)
    {
        _model = glm::translate(_model, glm::vec3(pos.x(), pos.y(), 0));
    }

    void Mesh::rotate(float dr)
    {
        _model = glm::rotate(_model, glm::radians(dr), glm::vec3(0, 0, 1));
    }

    void Mesh::setRotation(float angle)
    {
        float angle_rad = glm::radians(angle);
        float current_angle = glm::atan(_model[0][1], _model[0][0]);

        _model = glm::rotate(_model, (angle_rad - current_angle), glm::vec3(0, 0, 1));
    }

    void Mesh::updateBufferData(float* data)
    {
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, _vertex_count * 4 * sizeof(float), data);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Mesh::render(Matrix4f screen)
    {
        _shader->use();
        _shader->setMat4("model", _model);
        _shader->setMat4("screen", screen);
        _shader->setVec3("color", _color);
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _list_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        _shader->stop();
    }

}