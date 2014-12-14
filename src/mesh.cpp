
#include "mesh.h"
#include "display.h"

Mesh::Mesh (Display *display, int vertCount)
{
	// create VAO
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray (display->attrVertPos);
	
	// create VBO
	glGenBuffers (1, &vertexVbo);
	glBindBuffer (GL_ARRAY_BUFFER, vertexVbo);
	
	// set vertex attribute pointers
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, vertexVbo);
	glVertexAttribIPointer (display->attrVertPos, 2, GL_INT, 0, 0);
	
	// resize the buffer to initial size
	resize (vertCount);
	
	// unbind
	glBindVertexArray (0);
}

Mesh::~Mesh ()
{
}

void Mesh::resize (int vertCount)
{
	this->vertCount = vertCount;
	vertices = new int [vertCount * 2];
}

void Mesh::update ()
{
	glBindBuffer (GL_ARRAY_BUFFER, vertexVbo);
	glBufferData (GL_ARRAY_BUFFER, this->vertCount * 2 * sizeof (int),
		vertices, GL_DYNAMIC_DRAW);
}

void Mesh::draw ()
{
	glBindVertexArray (vao);
	glDrawArrays (GL_TRIANGLES, 0, vertCount);
	glBindVertexArray (0);
}

