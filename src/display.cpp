
#include <iostream>
#include "display.h"
#include "utils.h"

using namespace std;

Display::Display (int width, int height)
	: width (width), height (height)
{
	// set SDL-OpenGL options
	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE); // only use core functions
	
	// create window
	window = SDL_CreateWindow ("Yet Another Settlers Clone",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	
	if (window == NULL) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (EXIT_FAILURE);
	}
	
	// create OpenGL context
	glContext = SDL_GL_CreateContext (window);
	
	if (glContext == NULL) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (EXIT_FAILURE);
	}
	
	// enable VSync
	if (SDL_GL_SetSwapInterval (1) == -1) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (EXIT_FAILURE);
	}
	
	// init GLEW
	GLenum glewRes = glewInit ();
	if (glewRes != GLEW_OK) {
		cerr << "GLEW error: " << glewGetErrorString (glewRes) << endl;
		exit (EXIT_FAILURE);
	}
	
	// set clear color
	glClearColor (0.0, 0.0, 1.0, 1.0);
	
	// resize viewport
	
	// shaders
	GLuint vertexShader =
		compileShader ("res/shaders/vs.glslv", GL_VERTEX_SHADER);
	GLuint fragmentShader =
		compileShader ("res/shaders/fs.glslf", GL_FRAGMENT_SHADER);
	GLuint shaderProg = linkProgram (vertexShader, fragmentShader);
	glUseProgram (shaderProg);
	attrVertPos = glGetAttribLocation (shaderProg, "vertPos");
	
	// Output some status information
	cout << "OpenGL version: " << glGetString (GL_VERSION) << endl;
}

Display::~Display ()
{
}

GLuint Display::compileShader (const char *fileName, GLenum shaderType)
{
	char *shaderSrc = loadFile (fileName);
	
	GLuint shader = glCreateShader (shaderType);
	glShaderSource (shader, 1, &shaderSrc, NULL);
	glCompileShader (shader);
	
	GLint shaderParam;
	glGetShaderiv (shader, GL_COMPILE_STATUS, &shaderParam);
	
	if (shaderParam == GL_FALSE) {
		glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &shaderParam);
		char *infoLog = new char [shaderParam];
		glGetShaderInfoLog (shader, shaderParam, NULL, infoLog);
		cerr << "Shader compilation error: "
			<< (GL_VERTEX_SHADER ? "Vertex shader: " : "Fragment shader: ")
			<< endl << infoLog << endl;
		exit (EXIT_FAILURE);
	}
	
	delete shaderSrc;
	
	return shader;
}

GLuint Display::linkProgram (GLuint vertexShader, GLuint fragmentShader)
{
	GLuint program = glCreateProgram ();
	glAttachShader (program, vertexShader);
	glAttachShader (program, fragmentShader);
	glLinkProgram (program);
	
	GLint shaderParam;
	glGetProgramiv (program, GL_LINK_STATUS, &shaderParam);
	
	if (shaderParam == GL_FALSE) {
		glGetProgramiv (program, GL_INFO_LOG_LENGTH, &shaderParam);
		char *infoLog = new char [shaderParam];
		glGetProgramInfoLog (program, shaderParam, NULL, infoLog);
		cerr << "Shader linkage error:" << endl << infoLog << endl;
		exit (EXIT_FAILURE);
	}
	
	return program;
}

void Display::clear ()
{
	glClear (GL_COLOR_BUFFER_BIT);
}

void Display::present ()
{
	SDL_GL_SwapWindow (window);
}

void Display::resize (int width, int height)
{
	this->width = width;
	this->height = height;
	glViewport (0, 0, width, height);
}

