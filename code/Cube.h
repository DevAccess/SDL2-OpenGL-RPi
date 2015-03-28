#pragma once

#include <stdio.h>

#ifdef __linux__
// OpenGL includes for Raspberry Pi
#include <GL/glu.h>
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#else
// OpenGL includes for Windows
#include <gl\glew.h>
#include <SDL_opengl.h>
#endif

#include "globals.h"
#include "stb_image.h"

/**
 * Cube class
 * Cube rotates and has same texture on all 6 sides.
 */
class Cube
{
public:
	Cube();
	~Cube();
	/**
	* Init vertex data and texture if any.
	*/
	bool init();
	/**
	* Renders the cube.
	*/
	void render();
	/**
	 * Update cube state. Rotation in this case.
	 */
	void update();
private:
	bool m_render; // will render cube only when true

	float m_angle; // rotation angle

	// GL
	GLuint m_textures[1]; // One texture, but can be extended to multiple
	GLuint m_gVBO; // Vertex buffer object
};

