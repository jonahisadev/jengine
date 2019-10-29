#include "Shader.h"

namespace JEngine {

    Shader::Shader(const char *vsrc, const char *fsrc) {
        GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vshader, 1, &vsrc, nullptr);
        glCompileShader(vshader);
        compiler_check(vshader);
        
        GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fshader, 1, &fsrc, nullptr);
        glCompileShader(fshader);
        compiler_check(fshader);
        
        _program = glCreateProgram();
        glAttachShader(_program, vshader);
        glAttachShader(_program, fshader);
        glLinkProgram(_program);
        linker_check(_program);
        
        glDeleteShader(vshader);
        glDeleteShader(fshader);
    }

    Shader::~Shader() {
        stop();
        glDeleteProgram(_program);
    }

    void Shader::use() {
        glUseProgram(_program);
    }

    void Shader::stop() {
        glUseProgram(0);
    }

    void Shader::setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(_program, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
    }

    void Shader::setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
    }

    void Shader::setVec2(const std::string& name, const glm::vec2& value) const  {
        glUniform2fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec2(const std::string& name, float x, float y) const {
        glUniform2f(glGetUniformLocation(_program, name.c_str()), x, y);
    }

    void Shader::setVec3(const std::string& name, const glm::vec3& value) const  {
        glUniform3fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec3(const std::string& name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(_program, name.c_str()), x, y, z);
    }

    void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
        glUniform4f(glGetUniformLocation(_program, name.c_str()), x, y, z, w);
    }

    void Shader::setMat2(const std::string& name, const glm::mat2& value) const {
        glUniformMatrix2fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setMat3(const std::string& name, const glm::mat3& value) const {
        glUniformMatrix3fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
        glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::compiler_check(GLuint shader) {
        int success;
        char log[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, log);
            JERROR("Shader Compilation Error: %s", log);
        }
    }

    void Shader::linker_check(GLuint program) {
        int success;
        char log[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(program, 512, nullptr, log);
            JERROR("Shader Linker Error: %s", log);
        }
    }
    
    const char* Shader::DefaultQuadVertexShader =
            "#version 330 core\n"
            "layout (location = 0) in vec2 aPos;\n"
            "out vec4 v_color;\n"
            "uniform vec3 color;\n"
            "uniform mat4 model;\n"
            "uniform mat4 view;\n"
            "uniform mat4 projection;\n"
            "void main() {\n"
            "    gl_Position = projection * view * model * vec4(aPos, 0.0f, 1.0f);\n"
            "    v_color = vec4(color, 1.0f);\n"
            "}";
    
    const char* Shader::DefaultQuadFragmentShader =
            "#version 330 core\n"
            "in vec4 v_color;\n"
            "out vec4 FragColor;\n"
            "void main() {\n"
            "    FragColor = v_color;\n"
            "}\n";

}