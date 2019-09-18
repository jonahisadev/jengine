#include "Font.h"

namespace JEngine {
    
    FT_Library Font::_lib = nullptr;

    FontMesh::FontMesh(float *pos, float *color, int *els, int vCount, int lCount, GLuint tex)
    : Mesh(pos, color, els, vCount, lCount)
    {
        float uv[] = {
            0, 0,
            1, 0,
            1, 1,
            0, 1
        };
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[BufferCoords]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, uv, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        _buffers[BufferTexture] = tex;
        _textured = true;
    }

    Font::Font(const char* path, int size) {
        if (!_lib) {
            if (FT_Init_FreeType(&_lib)) {
                std::cerr << "Could not initialize FreeType library" << std::endl;
                throw;
            }
        }
        
        if (FT_New_Face(_lib, path, 0, &_face)) {
            std::cerr << "Failed to load font '" << path << "'" << std::endl;
            throw;
        }
        
        FT_Set_Pixel_Sizes(_face, 0, size);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        for (GLubyte c = 0; c < 128; c++) {
            if (FT_Load_Char(_face, c, FT_LOAD_RENDER)) {
                std::cerr << "Failed to load glyph: '" << c << "'" << std::endl;
                continue;
            }
            
            FT_Bitmap bitmap = _face->glyph->bitmap;
            unsigned int bitmap_size = bitmap.width * bitmap.rows;
            unsigned char data[bitmap_size * 4];
            
            for (unsigned int i = 0; i < bitmap_size; i++) {
                data[(i * 4) + 0] = 255;
                data[(i * 4) + 1] = 255;
                data[(i * 4) + 2] = 255;
                data[(i * 4) + 3] = bitmap.buffer[i];
            }
            
            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                _face->glyph->bitmap.width,
                _face->glyph->bitmap.rows,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
//                _face->glyph->bitmap.buffer 
                data
            );
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            Character character = {
                tex,
                Vector2i(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
                Vector2i(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
                static_cast<GLuint>(_face->glyph->advance.x)
            };
            _chars.insert(std::pair<GLchar, Character>(c, character));
        }
    }

    Font::~Font() {
        FT_Done_Face(_face);
    }

    void Font::render(float x, float y, const char *str, Vector3f color) {
        for (int i = 0; i < strlen(str); i++) {
            char c = str[i];
            Character ch = _chars[c];
            
            float xpos = x + ch.bearing.x();
            float ypos = y - ch.bearing.y();
            float width = ch.size.x();
            float height = ch.size.y();
            
//            std::cout << c << " @ (" << xpos << " , " << ypos << ")" << std::endl;
            
            float pos[] = {
                xpos, ypos,
                xpos + width, ypos,
                xpos + width, ypos + height,
                xpos, ypos + height
            };
            
            float col[] = {
                color.r(), color.g(), color.b(),
                color.r(), color.g(), color.b(),
                color.r(), color.g(), color.b(),
                color.r(), color.g(), color.b(),
            };
            
            int els[] = {
                0, 1, 2,
                0, 3, 2
            };
            
            FontMesh mesh(pos, col, els, 4, 6, ch.tex_id);
            mesh.render();
            x += (ch.advance >> 6);
        }
    }

    void Font::render(float x, float y, const std::string &str, Vector3f color) {
        render(x, y, str.c_str(), color);
    }

    float Font::width(const char *str) {
        float width = 0.0f;
        for (int i = 0; i < strlen(str); i++) {
            char c = str[i];
            Character ch = _chars[c];
            width += (ch.advance >> 6);
        }
        return width;
    }

    void Font::cleanup() {
        if (!_lib)
            FT_Done_FreeType(_lib);
    }

}