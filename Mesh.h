#pragma once
#include <GL/glew.h>
#include <iostream>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void clearMesh();
	void displayMesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

