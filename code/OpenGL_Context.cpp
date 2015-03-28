#include "OpenGL_Context.h"
#include "globals.h"
#include <fstream>
#include <string>

/**
 * Read text file
 * @Param filename. const char pointer to file name
 * Returns std::string containing file text
 */
std::string get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

OpenGL_Context::OpenGL_Context()
{}

#ifdef __linux__
/**
 * OGL functions for Raspberry Pi
 */
EGLConfig OpenGL_Context::getEGLConfig()
{
	return m_EGLConfig;
}
EGLContext OpenGL_Context::getRawContext()
{
	return m_gContext;
}
bool OpenGL_Context::RPi_OGLinit(EGLDisplay display)
{
	EGLint num_config;
	static const EGLint context_attributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};
	static const EGLint attribute_list[] =
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};

	m_gContext = EGL_NO_CONTEXT; // set default

	// get an appropriate EGL frame buffer configuration
	EGLBoolean result = eglChooseConfig(display, attribute_list, &m_EGLConfig, 1, &num_config);
	if(result == EGL_FALSE)
	{
		printf("Error getting EGL frame buffer configuration\n");
	}
	else
	{
		result = eglBindAPI(EGL_OPENGL_ES_API);
		if (result == EGL_FALSE)
		{
			printf("Error binding OGL ES API\n");
		}
		else
		{
			// create an EGL rendering context
			m_gContext = eglCreateContext(display, m_EGLConfig, EGL_NO_CONTEXT, context_attributes);
			if(m_gContext == EGL_NO_CONTEXT)
			{
				printf("Error creating EGL context\n");
			}
		}
	}
	return m_gContext != EGL_NO_CONTEXT;
}
#endif
/**
* OGL setup functions for Windows
*/
bool OpenGL_Context::SDL_OGLinit( SDL_Window* gWindow )
{
	m_gContext = SDL_GL_CreateContext( gWindow );
	if (m_gContext != NULL)
	{
		// Use Vsync
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		}
	}
	else
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
	}
	return m_gContext != NULL;
}

bool OpenGL_Context::buildShaders()
{
	// create shaders
	shaders = new gShader[1];
	shaderCount = 1;
	bool success = true;
	// Build BASIC_TEXTURE shader
	// Get vertex and fragment source
	std::string tmp = get_file_contents("basic_texture.vert");
	const GLchar * vsText = tmp.c_str();
	std::string tmp2 = get_file_contents("basic_texture.frag");
	const GLchar * fsText = tmp2.c_str();
	if(vsText == NULL || fsText == NULL)
	{
		success = false;
	}
	else
	{
		printf("Building Shader\n");
		if(!buildShaderProgram(shader_t::BASIC_TEXTURE_SHADER, &vsText, &fsText))
		{
			printf("Failed!\n");
			success = false;
		}
		else
		{ // Mark shader as valid
			shaders[shader_t::BASIC_TEXTURE_SHADER].valid = true;
			// Get attribute locations
			shaders[shader_t::BASIC_TEXTURE_SHADER].vertexPosAttr = glGetAttribLocation(shaders[shader_t::BASIC_TEXTURE_SHADER].gProgramID, "LVertexPos");
			shaders[shader_t::BASIC_TEXTURE_SHADER].vertexColorAttr = glGetAttribLocation(shaders[shader_t::BASIC_TEXTURE_SHADER].gProgramID, "LVertexColor");
			shaders[shader_t::BASIC_TEXTURE_SHADER].texCoordAttr = glGetAttribLocation(shaders[shader_t::BASIC_TEXTURE_SHADER].gProgramID, "LTexCoord");
			// Check for errors
			if (shaders[shader_t::BASIC_TEXTURE_SHADER].vertexPosAttr == -1)
			{
				printf("LVertexPos is not a valid glsl program variable!\n");
				success = false;
			}
			if (shaders[shader_t::BASIC_TEXTURE_SHADER].vertexColorAttr == -1)
			{
				printf("LVertexColor is not a valid glsl program variable!\n");
				success = false;
			}
			if (shaders[shader_t::BASIC_TEXTURE_SHADER].texCoordAttr == -1)
			{
				printf("LTexCoord is not a valid glsl program variable!\n");
				success = false;
			}
		}
	}
	return success;
}
bool OpenGL_Context::buildShaderProgram(shader_t shader, const GLchar** vertexShaderSource, const GLchar** fragmentShaderSource)
{
	bool success = true;
	// Create program
	shaders[shader].gProgramID = 0;
	shaders[shader].gProgramID = glCreateProgram();
	// Create vertex shader
	shaders[shader].vProgramID = glCreateShader( GL_VERTEX_SHADER );
	// Set vertex source
	glShaderSource( shaders[shader].vProgramID, 1, vertexShaderSource, NULL );
	// Compile vertex source
	glCompileShader( shaders[shader].vProgramID );
	// Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv( shaders[shader].vProgramID, GL_COMPILE_STATUS, &vShaderCompiled );
	if( vShaderCompiled != GL_TRUE )
	{
		printShaderLog( shaders[shader].vProgramID );
        success = false;
	}
	else
	{
		// Attach vertex shader to program
		glAttachShader( shaders[shader].gProgramID, shaders[shader].vProgramID );

		// Create fragment shader
		shaders[shader].fProgramID = glCreateShader( GL_FRAGMENT_SHADER );

		// Set fragment source
		glShaderSource( shaders[shader].fProgramID, 1, fragmentShaderSource, NULL );
		// Compile fragment source
		glCompileShader( shaders[shader].fProgramID );

		// Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv( shaders[shader].fProgramID, GL_COMPILE_STATUS, &fShaderCompiled );
		if( fShaderCompiled != GL_TRUE )
		{
			printf( "Unable to compile fragment shader %d!\n", shaders[shader].fProgramID );
			printShaderLog( shaders[shader].fProgramID );
			success = false;
		}
		else
		{
			//Attach fragment shader to program
			glAttachShader( shaders[shader].gProgramID, shaders[shader].fProgramID );

			// Assign indexes
			glBindAttribLocation(shaders[shader].gProgramID, 0, "LVertexPos");
			glBindAttribLocation(shaders[shader].gProgramID, 1, "LVertexColor");
			glBindAttribLocation(shaders[shader].gProgramID, 2, "LTexCoord");

			//Link program
			glLinkProgram( shaders[shader].gProgramID );

			//Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv( shaders[shader].gProgramID, GL_LINK_STATUS, &programSuccess );
			if( programSuccess != GL_TRUE )
			{
				printf( "Error linking program %d!\n", shaders[shader].gProgramID );
				printProgramLog( shaders[shader].gProgramID );
				success = false;
			}
		}
	}
	return success;
}

OpenGL_Context::~OpenGL_Context()
{
	for(int i=0; i<shaderCount; i++)
	{
		glDetachShader(shaders[i].gProgramID, shaders[i].fProgramID);
		glDetachShader(shaders[i].gProgramID, shaders[i].vProgramID);

		glDeleteShader(shaders[i].fProgramID);
		glDeleteShader(shaders[i].vProgramID);
		glDeleteProgram(shaders[i].gProgramID);
	}
	delete [] shaders;
}

void OpenGL_Context::printShaderLog(GLuint shader)
{
	// Make sure shader is valid
	if (glIsShader(shader))
	{
		// Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		// Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// Allocate string
		char* infoLog = new char[maxLength];

		// Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			// Print Log
			printf("%s\n", infoLog);
		}

		// Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}

void OpenGL_Context::printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}
