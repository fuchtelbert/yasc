
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

class Display
{
public:
	Display (int width, int height);
	~Display ();
	void clear ();
	void present ();
	void resize (int width, int height);

	GLuint compileShader (const char *shaderSrc, GLenum shaderType);	
	GLuint linkProgram (GLuint vertexShader, GLuint fragmentShader);
	
	int width, height;
	SDL_Window *window;
	SDL_GLContext glContext;
	GLint attrVertPos;
};

#endif /* DISPLAY_H */

