cmake_minimum_required(VERSION 3.14)
project(jengine)

set(CMAKE_CXX_STANDARD 14)

add_library(jengine Display.cpp Display.h OpenGL.h Vertex2.cpp Vertex2.h)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-DJENGINE_MACOS)

    find_library(GL OpenGL)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)

    target_include_directories(jengine PUBLIC ${GLFW_INCLUDE_DIRS})
    target_link_libraries(jengine ${GL} ${GLFW_LIBRARIES})
    target_compile_options(jengine PUBLIC ${GLFW_CFLAGS_OTHER})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_definitions(-DJENGINE_LINUX)
    
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)

    target_link_libraries(jengine ${GLFW_LIBRARIES} dl GL rt Xrandr Xxf86vm Xi Xinerama X11 Xcursor pthread)
    target_include_directories(jengine PUBLIC ${GLFW_INCLUDE_DIRS})
    target_compile_options(jengine PUBLIC ${GLFW_CFLAGS_OTHER})
endif()