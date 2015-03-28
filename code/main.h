#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "X11/Xlib.h" // might be necessary for *nix comp

#include "SDL.h"

#ifdef __linux__
// bcm_host is only for raspberry pi
#include "bcm_host.h"
#else
// On Windows we use glew
#pragma comment(lib, "glew32.lib")
#include <gl\glew.h>
#endif

#pragma comment(lib, "opengl32.lib")

#include "OpenGL_Context.h"
#include "Cube.h"
#include "Window.h"

#include "globals.h"

// GLM headers
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#if defined _MSC_VER
#undef main // Undefine main due to SDL
#endif

/**
 * All functions in main
 */
int main();
bool init();
bool initGL();
void update();
void render();
void close();
