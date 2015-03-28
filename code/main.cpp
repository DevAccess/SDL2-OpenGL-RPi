#include "main.h"

// Define global cube and window
Cube cube;
Window window;

// global pointer to our OpenGL context
OpenGL_Context * gContext;

// initialize SDL, OpenGL, and create window
bool init()
{
#ifdef __linux__
	bcm_host_init(); // RPi needs this
#endif

	bool success = true;
	
	// Initialize SDL video subsystem
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !window.init() )
		{
			success = false;
		}
		else
		{
			// Get window size
			window.getWindowSize(windowWidth, windowHeight);
			printf( "Window width: %i\nWindow height: %i\n", windowWidth, windowHeight );
			if(windowWidth == 0 || windowHeight == 0)
			{
				printf( "Window size is invalid");
			}
			else
			{
				aspectRatio = windowWidth/(float)windowHeight;
			}

			// retrieve pointer to GL context
			gContext = window.getContext();

			// Output OGL version
			printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

#ifndef __linux__
			// GLEW is only used on Windows

			// Initialize GLEW
			printf("Initializing GLEW\n");
			glewExperimental = GL_TRUE;
			GLenum glewError = glewInit();
			if (glewError != GLEW_OK)
			{
				printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
			}
#endif

			// Initialize OpenGL Stuff
			printf( "Initializing OpenGL\n" );
			if( !initGL() )
			{
				printf("Unable to initialize OpenGL!\n");
				success = false;
			}
			printf( "Build Shaders\n" );
			// Build all shaders
			if(!gContext->buildShaders())
			{
				printf( "Error while building shaders!\n");
			}
		}
	}

	// init cube
	cube.init();

	return success;
}

bool initGL()
{
	bool success = true;

	float fov = 60.0;
	float nearPlane = 1.0f;
	float farPlane = 1000.0f;

	// Initialize viewport
	glViewport(0, 0, windowWidth, windowHeight);
	// Initialize projection matrix
	projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

	// setup identity view and model matrices
	viewMatrix = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);
	
	// Enable Stuff
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_SRC_COLOR);

	// Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	return success;
}

void update()
{
	cube.update();
}

void render()
{
	GLenum error = GL_NO_ERROR;

	// clear color buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

	pushMatrix();

	// Translate to view position
	translate(glm::vec3(0, 0, -200));

	// Enable Stuff
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

	//glBlendFunc(GL_ONE, GL_SRC_COLOR);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//sendMatrices(); // might not be needed

	// Draw cube
	cube.render();

	popMatrix();
}

void close()
{
	// Quit SDL subsystems
	SDL_Quit();
}

int main()
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		bool quit = false;

		// Event handler
		SDL_Event e;

		// Enable text input
		SDL_StartTextInput();

		int count = 0;

		/**
		* Program stops at 30 seconds or if user quits
		*  30 seconds * 60fps = 1800
		*/
		while( !quit && count < 1800 )
		{
			count++;
			// Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				// User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true; // Quit application
				}
				//////////////////////////////////////////////////////
				// Quit if mouse button is pressed and released
				//  Only for testing mouse input.
				if (e.type == SDL_MOUSEBUTTONUP)
				{
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);
					printf("Mouse Pos: x = %i y = %i\n", mouseX, mouseY);
					quit = true;
				}
				//////////////////////////////////////////////////////
			}
			// Check key states
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_ESCAPE])
			{ // User pressed escape key
				quit = true; // Quit application
			}

			// Update everything
			update();

			// draw
			render();

			// Update screen
			window.swap();
		}

	}
	// Free resources and close SDL
	close();

	return 0;
}







