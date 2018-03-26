//#include <iostream>
//
//int main() {
//	std::cout << "Hello World!";
//}

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

int main() {
	// Intialize GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLWF\n");
		return -1;
	}

	// Create an OpenGL Window
	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "Horsemen Engine", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW \n");
		return -1;
	}

	// Initialize Keyboard
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// Swap Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}