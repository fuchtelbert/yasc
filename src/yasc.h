
/*

NOTES:
* According to
  http://lazyfoo.net/tutorials/SDL/51_SDL_and_modern_opengl/index.php
  "gl/glew.h" must be included before any OpenGL header.
* According to
  https://www.opengl.org/wiki/OpenGL_Loading_Library
  with GLEW another OpenGL header is not needed to be included

*/

#ifndef YASC_H
#define YASC_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

class Yasc
{
public:
	Yasc ();
	~Yasc ();
	void run ();
	void handleInput ();
	void renderScene ();
	
	bool running;
	SDL_Window *window;
	SDL_GLContext glContext;
	Uint64 perfFreq;
	
	// OpenGL stuff
	GLuint glVertShader;
	GLuint glFragShader;
	GLuint glShaderProg;
};

#endif /* YASC_H */

