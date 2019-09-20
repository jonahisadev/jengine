# JEngine

JEngine is a cross-platform 2D C++ game engine. JEngine aims to provide the basic
elements of a game engine for simplicity and versatility.

At the moment, this is mostly for me so I can write games more easily

## Todo

These aren't in any particular order

* Graphics
  * Switch to VBO's for faster rendering
  * Meshes should glBufferSubData on translate
  * Mesh rotation
  * Spritesheets
  * Handle window resizing
  * Eventually move to OpenGL 3 and shader support
* Audio
  * Looping
  * Pause/Play/Stop
  * Move audio initialization to Game singleton
* Math
  * More vector operations
  * Vector4
* More configurations
  * Game singleton class for options

### Open Source Libraries

* [SOIL](https://www.lonesock.net/soil.html) (Public Domain)
* [GLEW](http://glew.sourceforge.net/) (BSD, MIT)
* [GLFW](https://glfw.org) (Zlib)
* [FreeType](https://www.freetype.org) (GPLv2)
* [OpenAL Soft](https://github.com/kcat/openal-soft) (LGPL)