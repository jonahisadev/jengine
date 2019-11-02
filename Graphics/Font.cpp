#include "Font.h"
#include "Display.h"

namespace JEngine {
    
    FT_Library Font::_lib = nullptr;

    FontMesh::FontMesh()
    : _shader(new Shader(Shader::DefaultTextureVertexShader, Shader::DefaultTextureFragmentShader)),
        _color({1, 1, 1}), _model(1.0f)
    {
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ebo);
        
        glBindVertexArray(_vao);
        
        float buffer[] = {
            0, 0, 0, 0,
            0, 0, 1, 0,
            0, 0, 1, 1,
            0, 0, 0, 1
        };
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), buffer, GL_STATIC_DRAW);
        
        int els[] = {
            0, 1, 2,
            0, 3, 2
        };
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), els, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    FontMesh::~FontMesh() {
        glDeleteTextures(1, &_tex);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        glDeleteVertexArrays(1, &_vao);
    }

    void FontMesh::render(Matrix4f screen) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _tex);
        
        _shader->use();
        _shader->setMat4("model", _model);
        _shader->setMat4("screen", screen);
        _shader->setVec3("color", _color);
        _shader->setInt("tex", 0);
        
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        _shader->stop();
    }

    void FontMesh::setPosition(float *pos) {
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        for (int i = 0; i < 4; i++) {
            float coord[2];
            coord[0] = pos[(i * 2) + 0];
            coord[1] = pos[(i * 2) + 1];
            glBufferSubData(GL_ARRAY_BUFFER, ((i * 4)) * sizeof(float), 2 * sizeof(float), coord);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void FontMesh::setColor(const Vector3f& color) {
        _color = color;
    }

    Font::Font(const char* path, int size, Display* d)
    : _projection(d->screen())
    {
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
            auto data = new unsigned char[bitmap_size * 4];
            
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
                data
            );
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            Character character = {
                tex,
                Vector2i(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
                Vector2i(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
                static_cast<GLuint>(_face->glyph->advance.x)
            };
            _chars.insert(std::pair<GLchar, Character>(c, character));
            
            delete[] data;
        }

        JINFO("(Font) Font library created");
    }

    Font::~Font() {
        FT_Done_Face(_face);
        JINFO("(Font) Font library destroyed");
    }

    void Font::render(float x, float y, const char *str, Vector3f color) {
        for (int i = 0; i < strlen(str); i++) {
            char c = str[i];
            Character ch = _chars[c];
            
            float xpos = x + ch.bearing.x();
            float ypos = y - ch.bearing.y();
            float width = (float)ch.size.x();
            float height = (float)ch.size.y();
            
//            std::cout << c << " @ (" << xpos << " , " << ypos << ")" << std::endl;
            
            float pos[] = {
                xpos, ypos,
                xpos + width, ypos,
                xpos + width, ypos + height,
                xpos, ypos + height
            };

            _mesh.setTextureID(ch.tex_id);
            _mesh.setPosition(pos);
            _mesh.setColor(color);
            _mesh.render(_projection);

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

    float Font::height(const char *str) {
        float height = 0.0f;
        for (int i = 0; i < strlen(str); i++) {
            char c = str[i];
            Character ch = _chars[c];
            if (height < ch.bearing.y())
                height = ch.size.y();
        }
        return height;
    }

    float Font::width(const std::string &str) {
        return width(str.c_str());
    }

    float Font::height(const std::string &str) {
        return height(str.c_str());
    }

    void Font::cleanup() {
        if (!_lib)
            FT_Done_FreeType(_lib);
    }

}