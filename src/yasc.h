
#ifndef YASC_H
#define YASC_H

#include <SDL2/SDL.h>
#include "display.h"

class Yasc
{
public:
	Yasc ();
	~Yasc ();
	
	void run ();
	void handleInput ();
	void renderScene ();
	
	bool running;
	Uint64 perfFreq;
	Display *display;
};

#endif /* YASC_H */

