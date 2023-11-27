#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	//ID reference of element buffer object
	GLuint ID;

	EBO(GLuint* indices, GLsizeiptr size);

	//Binds the EBO
	void Bind();
	//Unbinds the EBO
	void Unbind();
	// deletes the EBO
	void Delete();
};

#endif