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
 
    class FontMesh : public Mesh {
        
    public:
        FontMesh(float* pos, float* color, int* els, int vCount, int lCount, GLuint tex);
        virtual ~FontMesh();
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
    public:
        Font(const char* path, int size);
        virtual ~Font();
        
        void render(float x, float y, const char* str, Vector3f color);
        void render(float x, float y, const std::string& str, Vector3f color);
        
        float width(const char* str);
        
        static void cleanup();
    };

}