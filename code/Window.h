#pragma once

#include <string>
#include "OpenGL_Context.h"
#include "SDL.h"

#ifdef __linux__
// Includes specific to Raspberry Pi
#include "bcm_host.h"
#include "EGL/egl.h"
#endif

/**
* Window class is used to create a GUI window and to contain anything Window/GUI related.
**/
class Window
{
public:
	Window();
	~Window();
	/**
	 * Calls the proper initlaizer function for initializing and SDL or native linux window.
	 * Returns true on success, false otherwise.
	 */
	bool init();
	/**
	 * Returns window size in width and height params.
	 */
	void getWindowSize(int &width, int &height);
	/**
	 * Returns pointer to OpenGL context.
	 */
	OpenGL_Context * getContext();
	/**
	 * Swaps display buffer for rendering the current frame.
	 */
	void swap();

#ifdef __linux__
	/**
	 * Returns pointer to EGL Window.
	 */
	EGL_DISPMANX_WINDOW_T * getWindow();
	/**
	 * Returns EGL Display.
	 */
	EGLDisplay getDisplay();
#else
	/**
	 * Returns SDL window.
	 */
	SDL_Window * getWindow();
#endif

private:

	/**
	* Don't allow copies of this class to be created.
	* Removing the Window copy constructor and the
	*  assignment operator blocks anything from
	*  creating a copy of this class.
	*/
	Window(const Window& that) = delete;
	Window& operator=(const Window& that) = delete;

#ifdef __linux__
	/**
	 * Initlaization function specific to linux/RPi.
	 * Returns true on success, false otherwise.
	 */
	bool nativeWindowInit();
#else
	/**
	* Initialization function specific to SDL.
	* Returns true on success false otherwise.
	*/
	bool SDLWindowInit();

#endif

	OpenGL_Context m_context;
	int m_windowWidth;
	int m_windowHeight;

#ifdef __linux__
	/**
	 * Native window, display, and surface for use in linux/RPi
	 */
	EGL_DISPMANX_WINDOW_T m_window;
	EGLDisplay m_display;
	EGLSurface m_surface;
#else
	/**
	 * SDL Window
	 */
	SDL_Window* m_window;
#endif

};

