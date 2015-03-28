#pragma once

#include <stdio.h>
#include "SDL.h"

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

/**
 * Containement class for OpenGL context and related functions.
 * Class Initializes all shaders.
 */
class OpenGL_Context
{
public:
	OpenGL_Context();
	~OpenGL_Context();
	/**
	 * Initlaize OGL through SDL
	 * Returns true on success. false otherwise.
	 * @Param gWindow. Pointer to SDL window
	 */
	bool SDL_OGLinit( SDL_Window* gWindow );
	/**
	 * Reads shader files and builds all.
	 * Modifies global vars related to shaders in globals.h
	 * Returns true on success, false otherwise.
	 */
	bool buildShaders();

#ifdef __linux__
	/**
	 * Initalize OGL ES. Sepcific to RPi.
	 * Returns true on success, false otherwise.
	 */
	bool RPi_OGLinit(EGLDisplay display);
	/**
	 * Returns raw OGL context for certain uses.
	 */
	EGLContext getRawContext();
	/**
	 * Returns EGL config. Needed for setting up window.
	 */
	EGLConfig getEGLConfig();
#endif

private:
	/**
	* Don't allow copies of this class to be created.
	* Removing the OpenGL_Context copy constructor and
	*  the assignment operator blocks anything from
	*  creating a copy of this class.
	*/
	OpenGL_Context(const OpenGL_Context& that) = delete;
	OpenGL_Context& operator=(const OpenGL_Context& that) = delete;

	/**
	 * Used to build a given shader program.
	 * @Params: shader ID, vertex and fragment shader sources.
	 * Returns true on success, false otherwise.
	 */
	bool buildShaderProgram(shader_t pID, const GLchar** vertexShaderSource, const GLchar** fragmentShaderSource);

	/**
	 * Prints shader log for error.
	 */
	void printShaderLog(GLuint shader);
	/**
	 * Prints shader program log for error.
	 */
	void printProgramLog(GLuint program);

#ifdef __linux__
	/**
	 * EGL context and configuration.
	 */
	EGLContext m_gContext;
	EGLConfig m_EGLConfig;
#else
	/**
	 * SDL OGL context.
	 */
	SDL_GLContext m_gContext;
#endif

};

