#include "Cube.h"


Cube::Cube() : m_render(false), m_gVBO(0)
{
	// Make sure all textures are init to 0
	m_textures[0] = 0;
}

Cube::~Cube()
{}

bool Cube::init()
{
	bool success = true;

	// Vertex data
	vertex * vertices = new vertex[26];

	// Front face
	vertices[0].position[0] = -1.0f;
	vertices[0].position[1] = -1.0f;
	vertices[0].position[2] = 1.0f;
	vertices[0].color[0] = 1.0f;
	vertices[0].color[1] = 1.0f;
	vertices[0].color[2] = 1.0f;
	vertices[0].color[3] = 1.0f;
	vertices[0].texcoords[0] = 0.0f;
	vertices[0].texcoords[1] = 1.0f;

	vertices[1].position[0] = 1.0f;
	vertices[1].position[1] = -1.0f;
	vertices[1].position[2] = 1.0f;
	vertices[1].color[0] = 1.0f;
	vertices[1].color[1] = 1.0f;
	vertices[1].color[2] = 1.0f;
	vertices[1].color[3] = 1.0f;
	vertices[1].texcoords[0] = 1.0f;
	vertices[1].texcoords[1] = 1.0f;

	vertices[2].position[0] = -1.0f;
	vertices[2].position[1] = 1.0f;
	vertices[2].position[2] = 1.0f;
	vertices[2].color[0] = 1.0f;
	vertices[2].color[1] = 1.0f;
	vertices[2].color[2] = 1.0f;
	vertices[2].color[3] = 1.0f;
	vertices[2].texcoords[0] = 0.0f;
	vertices[2].texcoords[1] = 0.0f;

	vertices[3].position[0] = 1.0f;
	vertices[3].position[1] = 1.0f;
	vertices[3].position[2] = 1.0f;
	vertices[3].color[0] = 1.0f;
	vertices[3].color[1] = 1.0f;
	vertices[3].color[2] = 1.0f;
	vertices[3].color[3] = 1.0f;
	vertices[3].texcoords[0] = 1.0f;
	vertices[3].texcoords[1] = 0.0f;

	// Right face
	vertices[4].position[0] = 1.0f;
	vertices[4].position[1] = 1.0f;
	vertices[4].position[2] = 1.0f;
	vertices[4].color[0] = 1.0f;
	vertices[4].color[1] = 1.0f;
	vertices[4].color[2] = 1.0f;
	vertices[4].color[3] = 1.0f;
	vertices[4].texcoords[0] = 0.0f;
	vertices[4].texcoords[1] = 0.0f;

	vertices[5].position[0] = 1.0f;
	vertices[5].position[1] = -1.0f;
	vertices[5].position[2] = 1.0f;
	vertices[5].color[0] = 1.0f;
	vertices[5].color[1] = 1.0f;
	vertices[5].color[2] = 1.0f;
	vertices[5].color[3] = 1.0f;
	vertices[5].texcoords[0] = 0.0f;
	vertices[5].texcoords[1] = 1.0f;

	vertices[6].position[0] = 1.0f;
	vertices[6].position[1] = 1.0f;
	vertices[6].position[2] = -1.0f;
	vertices[6].color[0] = 1.0f;
	vertices[6].color[1] = 1.0f;
	vertices[6].color[2] = 1.0f;
	vertices[6].color[3] = 1.0f;
	vertices[6].texcoords[0] = 1.0f;
	vertices[6].texcoords[1] = 0.0f;

	vertices[7].position[0] = 1.0f;
	vertices[7].position[1] = -1.0f;
	vertices[7].position[2] = -1.0f;
	vertices[7].color[0] = 1.0f;
	vertices[7].color[1] = 1.0f;
	vertices[7].color[2] = 1.0f;
	vertices[7].color[3] = 1.0f;
	vertices[7].texcoords[0] = 1.0f;
	vertices[7].texcoords[1] = 1.0f;

	// Back face
	vertices[8].position[0] = 1.0f;
	vertices[8].position[1] = -1.0f;
	vertices[8].position[2] = -1.0f;
	vertices[8].color[0] = 1.0f;
	vertices[8].color[1] = 1.0f;
	vertices[8].color[2] = 1.0f;
	vertices[8].color[3] = 1.0f;
	vertices[8].texcoords[0] = 0.0f;
	vertices[8].texcoords[1] = 1.0f;

	vertices[9].position[0] = -1.0f;
	vertices[9].position[1] = -1.0f;
	vertices[9].position[2] = -1.0f;
	vertices[9].color[0] = 1.0f;
	vertices[9].color[1] = 1.0f;
	vertices[9].color[2] = 1.0f;
	vertices[9].color[3] = 1.0f;
	vertices[9].texcoords[0] = 1.0f;
	vertices[9].texcoords[1] = 1.0f;

	vertices[10].position[0] = 1.0f;
	vertices[10].position[1] = 1.0f;
	vertices[10].position[2] = -1.0f;
	vertices[10].color[0] = 1.0f;
	vertices[10].color[1] = 1.0f;
	vertices[10].color[2] = 1.0f;
	vertices[10].color[3] = 1.0f;
	vertices[10].texcoords[0] = 0.0f;
	vertices[10].texcoords[1] = 0.0f;

	vertices[11].position[0] = -1.0f;
	vertices[11].position[1] = 1.0f;
	vertices[11].position[2] = -1.0f;
	vertices[11].color[0] = 1.0f;
	vertices[11].color[1] = 1.0f;
	vertices[11].color[2] = 1.0f;
	vertices[11].color[3] = 1.0f;
	vertices[11].texcoords[0] = 1.0f;
	vertices[11].texcoords[1] = 0.0f;

	// Left face
	vertices[12].position[0] = -1.0f;
	vertices[12].position[1] = 1.0f;
	vertices[12].position[2] = -1.0f;
	vertices[12].color[0] = 1.0f;
	vertices[12].color[1] = 1.0f;
	vertices[12].color[2] = 1.0f;
	vertices[12].color[3] = 1.0f;
	vertices[12].texcoords[0] = 0.0f;
	vertices[12].texcoords[1] = 0.0f;

	vertices[13].position[0] = -1.0f;
	vertices[13].position[1] = -1.0f;
	vertices[13].position[2] = -1.0f;
	vertices[13].color[0] = 1.0f;
	vertices[13].color[1] = 1.0f;
	vertices[13].color[2] = 1.0f;
	vertices[13].color[3] = 1.0f;
	vertices[13].texcoords[0] = 0.0f;
	vertices[13].texcoords[1] = 1.0f;

	vertices[14].position[0] = -1.0f;
	vertices[14].position[1] = 1.0f;
	vertices[14].position[2] = 1.0f;
	vertices[14].color[0] = 1.0f;
	vertices[14].color[1] = 1.0f;
	vertices[14].color[2] = 1.0f;
	vertices[14].color[3] = 1.0f;
	vertices[14].texcoords[0] = 1.0f;
	vertices[14].texcoords[1] = 0.0f;

	vertices[15].position[0] = -1.0f;
	vertices[15].position[1] = -1.0f;
	vertices[15].position[2] = 1.0f;
	vertices[15].color[0] = 1.0f;
	vertices[15].color[1] = 1.0f;
	vertices[15].color[2] = 1.0f;
	vertices[15].color[3] = 1.0f;
	vertices[15].texcoords[0] = 1.0f;
	vertices[15].texcoords[1] = 1.0f;

	// Bottom face
	vertices[16].position[0] = -1.0f;
	vertices[16].position[1] = -1.0f;
	vertices[16].position[2] = 1.0f;
	vertices[16].color[0] = 1.0f;
	vertices[16].color[1] = 1.0f;
	vertices[16].color[2] = 1.0f;
	vertices[16].color[3] = 1.0f;
	vertices[16].texcoords[0] = 0.0f;
	vertices[16].texcoords[1] = 0.0f;

	vertices[17].position[0] = -1.0f;
	vertices[17].position[1] = -1.0f;
	vertices[17].position[2] = -1.0f;
	vertices[17].color[0] = 1.0f;
	vertices[17].color[1] = 1.0f;
	vertices[17].color[2] = 1.0f;
	vertices[17].color[3] = 1.0f;
	vertices[17].texcoords[0] = 0.0f;
	vertices[17].texcoords[1] = 1.0f;

	vertices[18].position[0] = 1.0f;
	vertices[18].position[1] = -1.0f;
	vertices[18].position[2] = 1.0f;
	vertices[18].color[0] = 1.0f;
	vertices[18].color[1] = 1.0f;
	vertices[18].color[2] = 1.0f;
	vertices[18].color[3] = 1.0f;
	vertices[18].texcoords[0] = 1.0f;
	vertices[18].texcoords[1] = 0.0f;

	vertices[19].position[0] = 1.0f;
	vertices[19].position[1] = -1.0f;
	vertices[19].position[2] = -1.0f;
	vertices[19].color[0] = 1.0f;
	vertices[19].color[1] = 1.0f;
	vertices[19].color[2] = 1.0f;
	vertices[19].color[3] = 1.0f;
	vertices[19].texcoords[0] = 1.0f;
	vertices[19].texcoords[1] = 1.0f;

	// Move to top face
	vertices[20].position[0] = 1.0f;
	vertices[20].position[1] = -1.0f;
	vertices[20].position[2] = -1.0f;
	vertices[20].color[0] = 1.0f;
	vertices[20].color[1] = 1.0f;
	vertices[20].color[2] = 1.0f;
	vertices[20].color[3] = 1.0f;
	vertices[20].texcoords[0] = 1.0f;
	vertices[20].texcoords[1] = 1.0f;

	vertices[21].position[0] = -1.0f;
	vertices[21].position[1] = 1.0f;
	vertices[21].position[2] = 1.0f;
	vertices[21].color[0] = 1.0f;
	vertices[21].color[1] = 1.0f;
	vertices[21].color[2] = 1.0f;
	vertices[21].color[3] = 1.0f;
	vertices[21].texcoords[0] = 0.0f;
	vertices[21].texcoords[1] = 1.0f;

	// Top face
	vertices[22].position[0] = -1.0f;
	vertices[22].position[1] = 1.0f;
	vertices[22].position[2] = 1.0f;
	vertices[22].color[0] = 1.0f;
	vertices[22].color[1] = 1.0f;
	vertices[22].color[2] = 1.0f;
	vertices[22].color[3] = 1.0f;
	vertices[22].texcoords[0] = 0.0f;
	vertices[22].texcoords[1] = 1.0f;

	vertices[23].position[0] = 1.0f;
	vertices[23].position[1] = 1.0f;
	vertices[23].position[2] = 1.0f;
	vertices[23].color[0] = 1.0f;
	vertices[23].color[1] = 1.0f;
	vertices[23].color[2] = 1.0f;
	vertices[23].color[3] = 1.0f;
	vertices[23].texcoords[0] = 1.0f;
	vertices[23].texcoords[1] = 1.0f;

	vertices[24].position[0] = -1.0f;
	vertices[24].position[1] = 1.0f;
	vertices[24].position[2] = -1.0f;
	vertices[24].color[0] = 1.0f;
	vertices[24].color[1] = 1.0f;
	vertices[24].color[2] = 1.0f;
	vertices[24].color[3] = 1.0f;
	vertices[24].texcoords[0] = 0.0f;
	vertices[24].texcoords[1] = 0.0f;

	vertices[25].position[0] = 1.0f;
	vertices[25].position[1] = 1.0f;
	vertices[25].position[2] = -1.0f;
	vertices[25].color[0] = 1.0f;
	vertices[25].color[1] = 1.0f;
	vertices[25].color[2] = 1.0f;
	vertices[25].color[3] = 1.0f;
	vertices[25].texcoords[0] = 1.0f;
	vertices[25].texcoords[1] = 0.0f;

	// Generate vertex buffer object
	glGenBuffers(1, &m_gVBO);

	// Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_gVBO);

	// Buffer vertex data
	glBufferData(GL_ARRAY_BUFFER, 26 * (3 + 4 + 2)*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	// clean up vertices
	delete[] vertices;
	// load Texture
	int n;
	int textureWidth;
	int textureHeight;
	GLbyte * textureData = (GLbyte*)stbi_load("cube.png", &textureWidth, &textureHeight, &n, 4);
	// assign to ogl texture
	glGenTextures(1, m_textures);
	glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLbyte*)textureData);

	if (success)
	{
		m_render = true;
	}
	return success;
}

void Cube::render()
{
	if (m_render)
	{
		// setup the first texture unit to use the texture
		glActiveTexture(GL_TEXTURE0);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, m_textures[0]);

		// Bind shader program
		bindShader(shader_t::BASIC_TEXTURE_SHADER);

		pushMatrix();

		// Transform cube
		rotate(m_angle, 1, 1, 0);
		scale(glm::vec3(50, 50, 50));
		// Send model/view/projection matrices to shader
		sendMatrices();

		// bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_gVBO);
		// Set attribute data pointers
		glVertexAttribPointer(shaders[shader_t::BASIC_TEXTURE_SHADER].vertexPosAttr, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
		glEnableVertexAttribArray(shaders[shader_t::BASIC_TEXTURE_SHADER].vertexPosAttr);
		glVertexAttribPointer(shaders[shader_t::BASIC_TEXTURE_SHADER].vertexColorAttr, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
		glEnableVertexAttribArray(shaders[shader_t::BASIC_TEXTURE_SHADER].vertexColorAttr);
		glVertexAttribPointer(shaders[shader_t::BASIC_TEXTURE_SHADER].texCoordAttr, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texcoords));
		glEnableVertexAttribArray(shaders[shader_t::BASIC_TEXTURE_SHADER].texCoordAttr);

		// Draw as triangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 26);
		// Unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		popMatrix(); // return to previous matrix state

		// Unbind program
		unbindShader();
	}
}

void Cube::update()
{
	// Increment cube rotation
	m_angle += 1;
	if (m_angle > 360)
	{
		m_angle = 0;
	}
}