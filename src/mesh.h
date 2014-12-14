
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

class Display;

class Mesh
{
public:
	Mesh (Display *display, int vertCount);
	~Mesh ();
	void resize (int vertCount);
	void update ();
	void draw ();
	
	GLuint vao;
	GLuint vertexVbo;
	int vertCount;
	int *vertices;
};

#endif /* MESH_H */

