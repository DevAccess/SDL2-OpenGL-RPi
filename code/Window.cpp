#include "Window.h"


Window::Window()
{
#ifndef __linux__ // m_window is only a pointer when using an SDL window
	m_window = NULL;
#endif
	m_windowWidth = 0;
	m_windowHeight = 0;
}

Window::~Window()
{
#ifndef __linux__
	// Destroy and nullify SDL window
	SDL_DestroyWindow(m_window);
	m_window = NULL;
#endif
}

void Window::getWindowSize(int &width, int &height)
{
	width = m_windowWidth;
	height = m_windowHeight;
}

OpenGL_Context * Window::getContext()
{
	return &m_context;
}

void Window::swap()
{
#ifdef __linux__
	eglSwapBuffers(m_display, m_surface);
#else
	SDL_GL_SwapWindow( m_window );
#endif
}

bool Window::init()
{
#ifdef __linux__
	return nativeWindowInit();
#else
	return SDLWindowInit();
#endif
}

#ifndef __linux__
SDL_Window * Window::getWindow()
{
	return m_window;
}
#endif

#ifndef __linux__
bool Window::SDLWindowInit()
{
	// Use OpenGL ES 2
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	// SDL_GL_SetAttribute(SDL_GL_ALHPA_SIZE, 8); // SDL_GL_ALHPA_SIZE not defined in RPi
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// Create window
	m_window = SDL_CreateWindow("SDL Window", 400, 400, 400, 400, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
	if (m_window == NULL)
	{
		printf("Window could not be created! %s\n", SDL_GetError() );
	}
	else
	{
		// get window dimensions
		SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
		// Create OGL context
		if(m_context.SDL_OGLinit(getWindow()))
		{
			return true;
		}
	}
	return false;
}
#endif

#ifdef __linux__
EGL_DISPMANX_WINDOW_T * Window::getWindow()
{
	return &m_window;
}
EGLDisplay Window::getDisplay()
{
	return m_display;
}

bool Window::nativeWindowInit()
{
	EGLBoolean result;

	VC_RECT_T dstRect;
	VC_RECT_T srcRect;

	// get an EGL display connection
	m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if(m_display == EGL_NO_DISPLAY)
	{
		printf("Error: Could not get an EGL display connection\n");
	}
	else if(glGetError() != 0)
	{
		printf("Error: OGL Error on display setup\n");
	}
	else
	{
		// initialize the EGL display connection
		result = eglInitialize(m_display, NULL, NULL);
		if(result == EGL_FALSE)
		{
			printf("Error initializing EGL display connection\n");
			return false;
		}
		else
		{
			// initialize EGL context
			if(m_context.RPi_OGLinit(getDisplay()))
			{
				// create an EGL window surface
				uint32_t screenWidth;
				uint32_t screenHeight;
				int32_t success = graphics_get_display_size(0 /* LCD */, &screenWidth, &screenHeight);
				if(success < 0 )
				{
					printf("Error creating an EGL window surface\n");
				}
				else
				{
					// set screen dimensions
					m_windowWidth = screenWidth;
					m_windowHeight = screenHeight;

					dstRect.width = screenWidth;
					dstRect.height = screenHeight;
					dstRect.x = 0;
					dstRect.y = 0;

					srcRect.width = screenWidth << 16;
					srcRect.height = screenHeight << 16;
					srcRect.x = 0;
					srcRect.y = 0;

					DISPMANX_DISPLAY_HANDLE_T dispmanDisplay = vc_dispmanx_display_open( 0 );
					DISPMANX_UPDATE_HANDLE_T dispmanUpdate = vc_dispmanx_update_start( 0 );

					DISPMANX_ELEMENT_HANDLE_T dispmanElement = vc_dispmanx_element_add( dispmanUpdate, dispmanDisplay,
						0/*layer*/, &dstRect, 0/*src*/,
						&srcRect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, DISPMANX_TRANSFORM_T::DISPMANX_NO_ROTATE/*transform*/);

					m_window.element = dispmanElement;
					m_window.width = screenWidth;
					m_window.height = screenHeight;
					vc_dispmanx_update_submit_sync( dispmanUpdate );
					printf("some output\n");
					if(glGetError() != 0)
					{
						printf("OpenGL Error!\n");
					}
					else
					{
						m_surface = eglCreateWindowSurface( m_display, m_context.getEGLConfig(), &m_window, NULL );
						if(m_surface == EGL_NO_SURFACE)
						{
							printf("Error creating EGL window surface\n");
						}
						else
						{
							// connect the context to the surface
							result = eglMakeCurrent(m_display, m_surface, m_surface, m_context.getRawContext());
							if(result == EGL_FALSE)
							{
								printf("Error connecting EGL context to surface.");
							}
							else
							{
								if(glGetError() != 0)
								{
									printf("OpenGL Error!\n");
								}
								else
								{
									// On Raspberry Pi, SDL window needs to be there to get mouse and keyboard input
									// Try and create SDL window
									SDL_Window* SDLWindow = NULL;
									SDLWindow = SDL_CreateWindow("SDL Window", 0, 0, m_windowWidth, m_windowHeight, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS);
									if (SDLWindow == NULL)
									{
										printf("SDL Window could not be created! %s\nMouse and keyboard input will not be supported.", SDL_GetError() );
									}
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}
#endif