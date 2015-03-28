#pragma once

#include <stdio.h>
#include <stack>

#ifdef __linux__
// OpenGL includes for Raspberry Pi
#include <GL/glu.h>
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#else
// OpenGL includes for Windows
#include <gl\glew.h>
#include <gl\GLU.h>
#include <SDL_opengl.h>
#endif

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Shaders are used by name from this ENUM
enum shader_t {BASIC_TEXTURE_SHADER};

// Shader definition. Not all shaders use all properties
struct gShader
{
	GLuint gProgramID;
	GLuint vProgramID;
	GLuint fProgramID;

	GLuint vertexPosAttr;
	GLuint vertexColorAttr;
	GLuint texCoordAttr;
	bool valid;
	gShader() : valid(false) {}
};
// vertex definition
typedef struct _vertex
{
	GLfloat position[3];
	GLfloat color[4];
	GLfloat texcoords[2];
} vertex;

// Global variables
////////////////////////////////////////////////////
extern int windowWidth;
extern int windowHeight;
extern float aspectRatio;

extern gShader* shaders;
extern int shaderCount;

extern glm::mat4 projectionMatrix;
extern glm::mat4 viewMatrix;
extern glm::mat4 modelMatrix;

extern std::stack<glm::mat4> projectionMatrices;
extern std::stack<glm::mat4> viewMatrices;
extern std::stack<glm::mat4> modelMatrices;

extern int projectionMatrixLocation;
extern int viewMatrixLocation;
extern int modelMatrixLocation;
////////////////////////////////////////////////////

// Utility functions used for graphics rendering
////////////////////////////////////////////////////

/**
 * Used to send model/view/projection matrices to current shader
 */
void sendMatrices();

/**
 * Transformation functions used to transform current view matrix
 */
void translate(glm::vec3 vec);
void scale(glm::vec3 vec);
void rotate(float angle, float x, float y, float z);

/**
 * Push and pop methods used the same as OpenGL's old fixed function pipeline.
 */
void pushMatrix();
void popMatrix();

/**
 * Use to bind a shader
 * @Param shader_t enum value. Value from shader enum
 */
void bindShader(shader_t shader);
void unbindShader();

////////////////////////////////////////////////////