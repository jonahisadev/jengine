#pragma once

#include <glm/glm.hpp>

#if defined(JENGINE_WINDOWS)
    #define GLEW_STATIC
    #include <GL/glew.h>
#elif defined(JENGINE_MACOS)
    #include <OpenGL/gl3.h>
#elif defined(JENGINE_LINUX)
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
#endif

namespace JEngine {
    typedef glm::mat4 Matrix4f;
}