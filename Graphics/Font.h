#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "OpenGL.h"
#include "Mesh.h"
#include "../Math/Vector.h"

#include <iostream>
#include <map>
#include <cstring>
#include <string>

namespace JEngine {
 
    class FontMesh {
    protected:
        GLuint _buffers[Mesh::BufferCount];
        GLuint _tex;

    public:
        FontMesh();
        ~FontMesh();

        inline void setTextureID(GLuint tex) { _tex = tex; };
        void render();
        void setPosition(float* pos);
        void setColor(float* color);
    };
    
    class Font {
    public:
        struct Character {
            GLuint tex_id;
            Vector2i size;
            Vector2i bearing;
            GLuint advance;
        };
        typedef std::map<char, Character> CharMap;
        
        static FT_Library _lib;
        FT_Face _face;
        CharMap _chars;
        FontMesh _mesh;
    public:
        Font(const char* path, int size);
        virtual ~Font();
        
        void render(float x, float y, const char* str, Vector3f color);
        void render(float x, float y, const std::string& str, Vector3f color);
        
        float width(const char* str);
        
        static void cleanup();
    };

}