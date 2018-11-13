#pragma once
//Ovo ovdje ucitava shadere i openGL 
#include <iostream>
#include <GL/glew.h>
#include <fstream>
#include <cstring>


using namespace std;

class ShaderLoader {
public:
	char *code; // test public variable

	ShaderLoader();
	~ShaderLoader();

	void clear();
	ShaderLoader(const GLchar *vertexPath, const GLchar *fragmentPath);
	void AddShaders(GLuint referenceProgram, const char* sourceCode, GLenum referenceEnum);
	char* readFile(const char* fileLocation);
	void useProgram();

	GLuint getProjection() { return uniformProjection; }
	GLuint getModel() { return uniformModel; }
	GLuint getView() { return uniformView; }

private:
	GLuint program, uniformModel, uniformProjection, uniformView;
	

};