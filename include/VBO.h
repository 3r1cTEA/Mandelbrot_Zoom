#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	// Reference ID of VBO
	GLuint ID;
	// constructor that generates a Vertex Buffer Objet and links to vertices
	VBO(GLfloat* vertices, GLsizeiptr);

	//Binds the VBO
	void Bind();

	//Unbinds the VBO
	void Unbind();

	//deletes the VBO
	void Delete();
};

#endif