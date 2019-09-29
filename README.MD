# JEngine

JEngine is a cross-platform 2D C++ game engine. JEngine aims to provide the basic
elements of a game engine for simplicity and versatility.

At the moment, this is mostly for me so I can write games more easily

## Features

* Cross-platform (tested on Windows, Mac and Linux)
* Easy to get up and running (minimal startup code)
* Basic quad/texture rendering
* Font loading and rendering (TTF)
* WAV loading and playback

## Todo

These aren't in any particular order

* Graphics
  * Better spritesheet support
  * Eventually move to OpenGL 3 and shader/VAO support
  * Allow cursor hide / replacement
* Audio
  * Looping
  * Pause/Play/Stop
* Math
  * More vector operations
  * Vector4
* Other
  * Restructure again for vendor and src directories

### Open Source Libraries

* [SOIL](https://www.lonesock.net/soil.html) (Public Domain)
* [GLEW](http://glew.sourceforge.net/) (BSD, MIT)
* [GLFW](https://glfw.org) (Zlib)
* [FreeType](https://www.freetype.org) (GPLv2)
* [OpenAL Soft](https://github.com/kcat/openal-soft) (LGPL)