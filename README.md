# Windows <-> Raspberry Pi crossplatform OpenGL ES SDL 2.0 c++ example #

I needed a solid codebase that would compile on both Windows and a Raspberry Pi. I wrote most of this from examples online, so anyone is free to use it however they want.

I used Visual Studio 2013 for compiling on Windows 7.
For the Raspberry Pi there is a makefile.

The program should create a fullscreen window, and display a rotating cube textured with cube.png.

Quite a few #ifdef's were used to get this to build on both Windows and the RPi.


### SDL 2.0 ###

On Windows, SDL is used to create the window. On the Raspberry Pi, the window is native and runs under X. The code is very similar to what's available from the OpenGL examples on any RPi.

SDL 2.0 will eventually be patched to work with OpenGL ES on the Raspberry Pi. When that happens I'll update the code to remove all the stuff native to the Raspberry Pi.

SDL is also used for user input.

## Notes ##

Only tested on Windows 7, and Raspbian.

This program contains a lot of boiler plate code involving shaders and the setup required.
If you just want to know how to get SDL 2.0 working on an RPi, look at the Window class and ignore code that is blocked out using #ifndef __linux__ as that is for Windows.


## Dependencies ##

Install the below dependencies.

 - SDL 2.0 (On the Raspberry Pi, I used this install script: https://www.dropbox.com/s/mpai8q1hpoju9xz/SDL2_install.sh)
 - GLM
 - GLEW

## Setup instructions on Visual Studio ##

Add the below libs under properties->Linker->Input

 - opengl32.lib
 - glew32.lib
 - SDL2.LIB
 - SDL2main.lib

Add your SDL include directory under properties->VC++ Directories

Add your SDL x86 lib directory under properties->VC++ Directories

You probably also need the SDL2.dll in your build directory, unless you set it up elsewhere.

Add your glm include directory under properties->VC++ Directories, or simply add the glm folder to your project folder.

*Done*

## Setup instructions on Raspberry Pi ##

Once all the dependencies are installed, all you have to do is attempt to build.

Using a terminal go to the directory with the makefile, and use make.

If there are any linker problems, add or modify dependencies in the makefile.

Should be fine if you're using Raspbian.

*Done*



