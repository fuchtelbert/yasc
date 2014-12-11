
#include <iostream>
#include <stdlib.h>
#include "yasc.h"
#include "utils.h"

const double framerateTarget = 60.0;
const double framelenTarget = 1.0 / framerateTarget;

using namespace std;

Yasc::Yasc ()
	: running (false), window (NULL), glContext (NULL)
{
	GLenum glenumRes;
	GLint glintRes;
	GLsizei glsizeiRes;
	
	// init SDL
	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (EXIT_FAILURE);
	}
	
	// set SDL-OpenGL options
	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE); // only use core functions
	
	// create window
	window = SDL_CreateWindow ("Yet Another Settlers Clone",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
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
	glenumRes = glewInit ();
	if (glenumRes != GLEW_OK) {
		cerr << "GLEW error: " << glewGetErrorString (glenumRes) << endl;
		exit (EXIT_FAILURE);
	}
	
	//
	// Shader stuff
	//
	
	glShaderProg = glCreateProgram ();

	char *vertShaderSrc = loadFile ("res/shaders/vs.glslv");
	
	glVertShader = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (glVertShader, 1, &vertShaderSrc, NULL);
	glCompileShader (glVertShader);
	
	glGetShaderiv (glVertShader, GL_COMPILE_STATUS, &glintRes);
	
	if (glintRes == GL_FALSE) {
		glGetShaderiv (glVertShader, GL_INFO_LOG_LENGTH, &glintRes);
		char *infoLog = (char*)malloc (glintRes);
		glGetShaderInfoLog (glVertShader, glintRes, &glsizeiRes, infoLog);
		cerr << "Vertex shader compilation error:" << endl << infoLog << endl;
		exit (EXIT_FAILURE);
	}
	
	glAttachShader (glShaderProg, glVertShader);
	
	char *fragShaderSrc = loadFile ("res/shaders/fs.glslf");
	
	glFragShader = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (glFragShader, 1, &fragShaderSrc, NULL);
	glCompileShader (glFragShader);
	
	glGetShaderiv (glFragShader, GL_COMPILE_STATUS, &glintRes);
	
	if (glintRes == GL_FALSE) {
		glGetShaderiv (glFragShader, GL_INFO_LOG_LENGTH, &glintRes);
		char *infoLog = (char*)malloc (glintRes);
		glGetShaderInfoLog (glFragShader, glintRes, &glsizeiRes, infoLog);
		cerr << "Fragment shader compilation error:" << endl << infoLog
			<< endl;
		exit (EXIT_FAILURE);
	}
	
	glAttachShader (glShaderProg, glFragShader);
	
	glLinkProgram (glShaderProg);
	
	glGetProgramiv (glShaderProg, GL_LINK_STATUS, &glintRes);
	
	if (glintRes == GL_FALSE) {
		glGetProgramiv (glShaderProg, GL_INFO_LOG_LENGTH, &glintRes);
		char *infoLog = (char*)malloc (glintRes);
		glGetProgramInfoLog (glShaderProg, glintRes, &glsizeiRes, infoLog);
		cerr << "Shader linkage error:" << endl << infoLog << endl;
		exit (EXIT_FAILURE);
	}
	
	// set clear color
	glClearColor (0, 0, 0, 1);
	
	// get performance frequency
	perfFreq = SDL_GetPerformanceFrequency ();
	
	// Output some status information
	cout << "OpenGL version: " << glGetString (GL_VERSION) << endl;
}

Yasc::~Yasc ()
{
}

void Yasc::run ()
{
	Uint64 nextFrameTick, now;
	
	nextFrameTick = now = SDL_GetPerformanceCounter ();
	running = true;
	
	while (running)
	{
		handleInput ();
		
		now = SDL_GetPerformanceCounter ();
		if (now >= nextFrameTick) {
			nextFrameTick += framelenTarget * perfFreq;
			renderScene ();
		}
	}
}

void Yasc::handleInput ()
{
	SDL_Event event;

	while (SDL_PollEvent (&event)) {
		switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
		}
	}
}

void Yasc::renderScene ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow (window);
}

