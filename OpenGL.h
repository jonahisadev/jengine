//
// Created by jonah on 9/16/19.
//

#pragma once

#if defined(JENGINE_WINDOWS)
    #include <GL/glew.h>
#elif defined(JENGINE_MACOS)
    #include <OpenGL/gl.h>
#elif defined(JENGINE_LINUX)
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
#endif