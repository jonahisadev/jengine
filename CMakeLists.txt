cmake_minimum_required(VERSION 3.10)
project(jengine)

set(CMAKE_CXX_STANDARD 17)

add_library(jengine Graphics/Display.cpp Graphics/Display.h Graphics/OpenGL.h Math/Vector2.h Graphics/Mesh.cpp Graphics/Mesh.h JEngine.h Graphics/Quad.cpp Graphics/Quad.h Graphics/TexturedMesh.cpp Graphics/TexturedMesh.h Graphics/TexturedQuad.cpp Graphics/TexturedQuad.h Math/Vector3.h Math/Vector.h Graphics/Font.cpp Graphics/Font.h Audio/Audio.cpp Audio/Audio.h Audio/WaveData.cpp Audio/WaveData.h Util/File.cpp Util/File.h Audio/Sound.cpp Audio/Sound.h Util/Bitmask.cpp Util/Bitmask.h Util/Logger.cpp Util/Logger.h Graphics/Spritesheet.cpp Graphics/Spritesheet.h Graphics/Shaders/Shader.cpp Graphics/Shaders/Shader.h Graphics/Scene.cpp Graphics/Scene.h Graphics/TextGroup.cpp Graphics/TextGroup.h Input/Controller.cpp Input/Controller.h Graphics/Animate.cpp Graphics/Animate.h Game/BaseGame.cpp Game/BaseGame.h Util/Ref.h Audio/Mp3Data.cpp Audio/Mp3Data.h Audio/AudioData.cpp Audio/AudioData.h Util/Timer.cpp Util/Timer.h Audio/Playlist.cpp Audio/Playlist.h Graphics/BasicQuad.cpp Graphics/BasicQuad.h Graphics/Sprite.cpp Graphics/Sprite.h)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DJENGINE_WINDOWS)
    set(GLFW_DIR "C:\\Users\\Jonah\\Dev\\LIBS\\GLFW")
    set(GLEW_DIR "C:\\Users\\Jonah\\Dev\\LIBS\\GLEW")
    set(SOIL_DIR "C:\\Users\\Jonah\\Dev\\LIBS\\SOIL")
    set(FT_DIR "C:\\Users\\Jonah\\Dev\\LIBS\\freetype2")
    set(AL_DIR "C:\\Users\\Jonah\\Dev\\LIBS\\OpenAL")
    set(GLM_DIR "C:\\Users\\Jonah\\Dev\\LIBS\\GLM")
    
    target_include_directories(jengine PUBLIC "${GLFW_DIR}\\include")
    target_include_directories(jengine PUBLIC "${GLEW_DIR}\\include")
    target_include_directories(jengine PUBLIC "${SOIL_DIR}\\include")
    target_include_directories(jengine PUBLIC "${FT_DIR}\\include")
    target_include_directories(jengine PUBLIC "${AL_DIR}\\include")
    target_include_directories(jengine PUBLIC "${GLM_DIR}\\include")
    
    target_link_directories(jengine PUBLIC "${GLFW_DIR}\\lib")
    target_link_directories(jengine PUBLIC "${GLEW_DIR}\\lib")
    target_link_directories(jengine PUBLIC "${SOIL_DIR}\\lib")
    target_link_directories(jengine PUBLIC "${FT_DIR}\\lib")
    target_link_directories(jengine PUBLIC "${AL_DIR}\\lib\\Win64")
    target_link_directories(jengine PUBLIC "${GLM_DIR}\\lib")
    
    target_link_libraries(jengine glfw3.lib glew32s.lib SOIL.lib opengl32.lib freetype.lib OpenAL32.lib)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-DJENGINE_MACOS)

    find_library(GL OpenGL)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)

    target_include_directories(jengine PUBLIC ${GLFW_INCLUDE_DIRS} /usr/local/include/freetype2)
    target_link_libraries(jengine ${GL} ${GLFW_LIBRARIES} SOIL freetype glm)
    target_compile_options(jengine PUBLIC ${GLFW_CFLAGS_OTHER})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_definitions(-DJENGINE_LINUX)
    set(ENV{PKG_CONFIG_PATH}  "/usr/local/lib/pkgconfig")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)

    target_link_libraries(jengine ${GLFW_LIBRARIES} dl GL rt Xrandr Xxf86vm Xi 
            Xinerama X11 Xcursor pthread SOIL freetype openal glm)
    target_include_directories(jengine PUBLIC ${GLFW_INCLUDE_DIRS} /usr/local/include/freetype2)
    target_compile_options(jengine PUBLIC ${GLFW_CFLAGS_OTHER})
endif()

install(TARGETS jengine DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/ 
        DESTINATION include/JEngine
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".git" EXCLUDE
        PATTERN "cmake-build-debug" EXCLUDE
        PATTERN ".idea" EXCLUDE
        PATTERN "build" EXCLUDE)