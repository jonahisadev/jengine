#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "OpenGL.h"
#include "Mesh.h"
#include "../Math/Vector.h"
#include "../Util/Logger.h"
#include "Display.h"

#include <iostream>
#include <map>
#include <cstring>
#include <string>

namespace JEngine {

    class Display;
    
    class FontMesh
    {
    protected:
        Shader* _shader;
        Vector3f _color;
        glm::mat4 _model;
        
        GLuint _vao, _vbo, _ebo;
        GLuint _tex;

    public:
        FontMesh();
        ~FontMesh();

        inline void setTextureID(GLuint tex) { _tex = tex; };
        void render(Matrix4f screen);
        void setPosition(float* pos);
        void setColor(const Vector3f& color);
    };
    
    class Font
    {
    public:
        struct Character {
            GLuint tex_id;
            Vector2i size;
            Vector2i bearing;
            GLuint advance;
        };
        typedef std::map<char, Character> CharMap;

        const Matrix4f& _projection;
        
        static FT_Library _lib;
        FT_Face _face;
        CharMap _chars;
        FontMesh _mesh;
    public:
        Font(const std::string& path, int size, Display* d);
        virtual ~Font();
        
        void render(float x, float y, const char* str, Vector3f color);
        void render(float x, float y, const std::string& str, Vector3f color);
        
        float width(const char* str);
        float width(const std::string& str);
        float height(const char* str);
        float height(const std::string& str);
        
        static void cleanup();
    };

}