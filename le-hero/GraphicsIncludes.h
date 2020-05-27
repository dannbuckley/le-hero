/**
 * SDLIncludes.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <GL\GL.h>

#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew-2_1_0/lib/glew32.lib")
#pragma comment(lib, "sdl2-2_0_12/lib/SDL2.lib")
#pragma comment(lib, "sdl2-2_0_12/lib/SDL2main.lib")
#pragma comment(lib, "sdl2_image-2_0_5/lib/SDL2_image.lib")
#endif