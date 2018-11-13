#include <iostream>
#include "ShaderLoader.h"
#include "Mesh.h"
#include "GLFW/glfw3.h"
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600; 
int screenWidth, screenHeight;


Mesh triangle1;
Mesh triangle2;
ShaderLoader shader;

const char* vertexPath = "resources/shaders/shader.vs";
const char* fragmentPath = "resources/shaders/shader.fs";

void createObjects()
{

	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	triangle1 = Mesh();
	triangle1.createMesh(vertices, indices, 12, 12);
	
	triangle2 = Mesh();
	triangle2.createMesh(vertices, indices, 12, 12);
	
}

void enableShaders()
{
	shader = ShaderLoader(vertexPath, fragmentPath);
}


int main()
{
	if (!glfwInit())
	{

		cout << "Could not initialize glfw." << endl;
		glfwTerminate();
		return 1;

	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GoldSpark Engine Test", nullptr, nullptr);
	
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr)
	{
		cout << "Window could not be created." << endl;
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		cout << "Could not initialize GLEW";
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	glewExperimental = true;

	glEnable(GL_DEPTH_TEST);
	
	

	glViewport(0, 0, screenWidth, screenHeight);
	
	enableShaders();
	createObjects();
	

	
	while(!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.useProgram();

		
		


		triangle1.displayMesh();
		triangle2.displayMesh();


		

		glUseProgram(0);



		glfwSwapBuffers(window);
	}

	triangle1.clearMesh();
	triangle2.clearMesh();
	shader.clear();
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}