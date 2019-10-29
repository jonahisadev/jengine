#pragma once

#include <glm/glm.hpp>
#include "../OpenGL.h"
#include "../../Util/Logger.h"

namespace JEngine {

    class Shader {
    public:
        enum Type {
            VertexShader,
            FragmentShader
        };
        
        static const char* DefaultQuadVertexShader;
        static const char* DefaultQuadFragmentShader;
        
    private:
        Type _type;
        GLuint _program;
        
        void compiler_check(GLuint shader);
        void linker_check(GLuint program);
        
    public:
        explicit Shader(const char* vsrc = DefaultQuadVertexShader, const char* fsrc = DefaultQuadFragmentShader);
        virtual ~Shader();
        
        void use();
        void stop();
        
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w) const;
        void setMat2(const std::string& name, const glm::mat2& value) const;
        void setMat3(const std::string& name, const glm::mat3& value) const;
        void setMat4(const std::string& name, const glm::mat4& value) const;
    };

}