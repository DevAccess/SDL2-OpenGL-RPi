#include "globals.h"

/**
 * Initialize all global extern variables
 */
///////////////////////////////////////////////////////////////

int windowWidth = 0;
int windowHeight = 0;
float aspectRatio = 1.0f;

gShader* shaders;
int shaderCount = 0;

glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;
glm::mat4 modelMatrix;

std::stack<glm::mat4> projectionMatrices;
std::stack<glm::mat4> viewMatrices;
std::stack<glm::mat4> modelMatrices;
enum MatrixModes {};

int projectionMatrixLocation;
int viewMatrixLocation;
int modelMatrixLocation;

///////////////////////////////////////////////////////////////

void bindShader(shader_t shader)
{
	if (shaders[shader].valid)
	{
		glUseProgram(shaders[shader].gProgramID);
		projectionMatrixLocation = glGetUniformLocation(shaders[shader].gProgramID, "projectionMatrix"); // Get location of the projection matrix in the shader
		viewMatrixLocation = glGetUniformLocation(shaders[shader].gProgramID, "viewMatrix"); // Get location of the view matrix in the shader
		modelMatrixLocation = glGetUniformLocation(shaders[shader].gProgramID, "modelMatrix"); // Get location of the model matrix in the shader
	}
	else
	{
		printf("Error: Attempting to use invalid shader!\n");
	}
}
void unbindShader()
{
	glUseProgram(0);
}

void sendMatrices()
{
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send model matrix to the shader
}

void translate(glm::vec3 vec)
{
	viewMatrix = glm::translate(viewMatrix, vec);
}
void scale(glm::vec3 vec)
{
	viewMatrix = glm::scale(viewMatrix, vec);
}
void rotate(float angle, float x, float y, float z)
{
	viewMatrix = glm::rotate(viewMatrix, angle, glm::vec3(x,y,z));
}

void pushMatrix()
{
	projectionMatrices.push(projectionMatrix);
	viewMatrices.push(viewMatrix);
	modelMatrices.push(modelMatrix);
}
void popMatrix()
{
	projectionMatrix = projectionMatrices.top();
	projectionMatrices.pop();
	viewMatrix = viewMatrices.top();
	viewMatrices.pop();
	modelMatrix = modelMatrices.top();
	modelMatrices.pop();
}
