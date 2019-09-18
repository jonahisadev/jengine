#include "Font.h"

namespace JEngine {
    
    FT_Library Font::_lib = nullptr;

    FontMesh::FontMesh() {
        glGenBuffers(Mesh::BufferCount, _buffers);

        glBindBuffer(GL_ARRAY_BUFFER, _buffers[Mesh::BufferPosition]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, nullptr, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, _buffers[Mesh::BufferColor]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 4, nullptr, GL_DYNAMIC_DRAW);

        float uv[] = {
            0, 0,
            1, 0,
            1, 1,
            0, 1
        };

        glBindBuffer(GL_ARRAY_BUFFER, _buffers[Mesh::BufferCoords]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, uv, GL_STATIC_DRAW);

        int els[] = {
            0, 1, 2,
            0, 3, 2
        };

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[Mesh::BufferIndex]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, els, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    FontMesh::~FontMesh() {
        glDeleteBuffers(Mesh::BufferCount, _buffers);
    }

    void FontMesh::render() {
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[Mesh::BufferPosition]);
        glVertexPointer(2, GL_FLOAT, 0, 0);
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, _buffers[Mesh::BufferColor]);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glEnableClientState(GL_COLOR_ARRAY);

        glBindTexture(GL_TEXTURE_2D, _tex);
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[Mesh::BufferCoords]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[Mesh::BufferIndex]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void FontMesh::setPosition(float *pos) {
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[Mesh::BufferPosition]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 2 * 4, pos);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void FontMesh::setColor(float *color) {
        glBindBuffer(GL_ARRAY_BUFFER, _buffers[Mesh::BufferColor]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * 4, color);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
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

            _mesh.setTextureID(ch.tex_id);
            _mesh.setPosition(pos);
            _mesh.setColor(col);
            _mesh.render();

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