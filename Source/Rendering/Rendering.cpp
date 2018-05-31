#include "HorsemanStd.h"
#include "HorsemanStd.h"
#include "Rendering.h"

#include "Shader.h"
#include "Components/Camera.h"

Rendering::Rendering() {
}

Rendering::~Rendering()
{
}

int Rendering::Init(const char* title) {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create an OpenGL Window
	if (config.DisplayMode == 1) {
		m_pWindow = glfwCreateWindow((int)config.ScreenWidth, (int)config.ScreenHeight, title, glfwGetPrimaryMonitor(), NULL);
	}
	else {
		m_pWindow = glfwCreateWindow((int)config.ScreenWidth, (int)config.ScreenHeight, title, NULL, NULL);
	}


	if (m_pWindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_pWindow);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW \n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Set background color 
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Uncomment to enable backface culling
	glEnable(GL_CULL_FACE);

	return 1;
}

int Rendering::LoadContent() {
	// Load MVP matrix

	return 1;
}

void Rendering::Begin() {
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Rendering::End() {
	// Swap Buffers
	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
}

void Rendering::Cleanup() {
	glfwTerminate();
}

void Rendering::SetWindowTitle(const char * title)
{
	glfwSetWindowTitle(m_pWindow, title);
}