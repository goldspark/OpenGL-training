#include "ShaderLoader.h"


ShaderLoader::ShaderLoader()
{
	program = 0;
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;

	code = nullptr;

}

void ShaderLoader::clear()
{
	if (program != 0)
	{
		glDeleteProgram(program);
		program = 0;
	}
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;

}

ShaderLoader::~ShaderLoader()
{
	clear();
	
}


char* ShaderLoader::readFile(const char* fileLocation)
{
	bool firstCopy = true;
	char *continuation = new char[1024];
	code = new char[10000];

	ifstream file(fileLocation, ios::in);
	if (!file.is_open())
	{
		cout << "Cannot open " << fileLocation << endl;
		file.close();
		return nullptr;
	}


	while (!file.eof())
	{
		char *line = new char[1024];
		file.getline(line, strlen(line) - 1);

		if (!firstCopy)
		{

			strcat_s(code, 10000, "\n");
			strcat_s(code, 10000, line);
		}
		if (firstCopy)
		{
			strcpy_s(code, 10000, line);
			firstCopy = false;
		}

		delete[] line;


	}


	file.close();

	delete[] continuation;


	return code;
}


void ShaderLoader::AddShaders(GLuint referenceProgram, const char* sourceCode, GLenum referenceEnum)
{

	GLuint shader = glCreateShader(referenceEnum);
	if (!shader)
	{
		cout << " Could not create shader." << endl;
		return;
	}

	const GLchar* src[1];
	src[0] = sourceCode;
	GLint size[1];
	size[0] = strlen(sourceCode);
	
	
	GLchar log[1024] = { 0 };
	int success = 0;

	glShaderSource(shader, 1, src, size);
	glCompileShader(shader);
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
		cout << "Shader compilation failed: " << log <<endl;
		return;
	}


	glAttachShader(program, shader);

	
}


ShaderLoader::ShaderLoader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
	
	const char* vertexSource = readFile(vertexPath);
	const char* fragmentSource = readFile(fragmentPath);
	
	delete[] code;


	program = glCreateProgram();

	if (!program)
	{
		std::cout << "Could not create program" << std::endl;
	}

	AddShaders(program, vertexSource, GL_VERTEX_SHADER);
	AddShaders(program, fragmentSource, GL_FRAGMENT_SHADER);

	GLchar log[1024] = { 0 };
	int success = 0;

	
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, sizeof(log), nullptr, log);
		cout << "Program linking failed: " << log << endl;
		return;
	}

	

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, sizeof(log), nullptr, log);
		cout << "Program validation failed: " << log << endl;
		return;
	}

	uniformModel = glGetUniformLocation(program, "model");
	uniformProjection = glGetUniformLocation(program, "projection");
	uniformView = glGetUniformLocation(program, "view");

}





void ShaderLoader::useProgram()
{
	glUseProgram(this->program);
}


