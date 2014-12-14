
#include <iostream>
#include <stdlib.h>
#include "yasc.h"
#include "utils.h"
#include "mesh.h"

using namespace std;

const double framerateTarget = 60.0;
const double framelenTarget = 1.0 / framerateTarget;
const int tria [] = {
	0, 0,
	1, 0,
	0, 1,
};


Mesh *testMesh;


Yasc::Yasc ()
	: running (false)
{
	// init SDL
	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (EXIT_FAILURE);
	}
	
	// init display
	display = new Display (800, 600);
	
	// get performance frequency
	perfFreq = SDL_GetPerformanceFrequency ();
	
	
	testMesh = new Mesh (display, 3);
	memcpy (testMesh->vertices, tria, 6 * sizeof(int));
	testMesh->update ();
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
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					display->resize (event.window.data1, event.window.data2);
				}
				break;
		}
	}
}

void Yasc::renderScene ()
{
	display->clear ();
	testMesh->draw ();
	display->present ();
}

