#include "HorsemanStd.h"
#include "Rendering.h"

#include "Shaders.h"
#include "Components/Camera.h"

Rendering::Rendering() {
	m_pShaders = new Shaders();
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
	m_pWindow = glfwCreateWindow((int)WIDTH, (int)HEIGHT, title, NULL, NULL);
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
	m_Handles["MatrixID"] = glGetUniformLocation(m_Handles["ProgramID"], "MVP");
	m_Handles["ModelMatID"] = glGetUniformLocation(m_Handles["ProgramID"], "M");
	m_Handles["ViewMatID"] = glGetUniformLocation(m_Handles["ProgramID"], "V");
	m_Handles["TextureID"] = glGetUniformLocation(m_Handles["ProgramID"], "textureSampler");

	glUseProgram(m_Handles["ProgramID"]);
	m_Handles["LightID"] = glGetUniformLocation(m_Handles["ProgramID"], "LightPosition_worldspace");

	return 1;
}

bool Rendering::LoadShader(const char* program, const char* vertexPath, const char* fragmentPath) {
	GLuint result = m_pShaders->LoadShaders(vertexPath, fragmentPath);
	if (result == 0) {
		return false;
	}
	m_Handles[program] = result;
	return true;
}

void Rendering::Update(float dt) {
}

int Rendering::Render(Camera* cam) {
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Swap Buffers
	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();

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
	glDeleteProgram(m_ProgramID);

	glfwTerminate();

	SAFE_DELETE(m_pShaders);
}

void Rendering::SetWindowTitle(const char * title)
{
	glfwSetWindowTitle(m_pWindow, title);
}

map<string, GLuint> Rendering::Handles()
{
	return m_Handles;
}
