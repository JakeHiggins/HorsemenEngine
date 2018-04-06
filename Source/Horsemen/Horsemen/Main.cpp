#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

static const GLfloat g_VertexBufferData[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader from file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Failed to open vertex shader %s", vertex_file_path);
		getchar();
		return 0;
	}

	// Read fragment shader
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);

	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else {
		printf("Failed to open fragment shader %s", fragment_file_path);
		getchar();
		return 0;
	}

	GLint result = GL_FALSE;
	int InfoLogLength;

	// Compile vertex shader
	printf("Compiling vertex shader : %s\n", vertex_file_path);
	const char* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check vertex shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile fragment shader
	printf("Compiling fragment shader : %s\n", fragment_file_path);
	const char* FragmentShaderPointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentShaderPointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	// Clean up shaders
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

int main() {
	// Intialize GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLWF\n");
		return -1;
	}

	// Create an OpenGL Window
	GLFWwindow* m_Window;
	m_Window = glfwCreateWindow(1024, 768, "Horsemen Engine", NULL, NULL);
	if (m_Window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_Window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW \n");
		return -1;
	}

	// Create VAO
	GLuint m_VertexArrayID;
	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	GLuint m_VertexBuffer;
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_VertexBufferData), g_VertexBufferData, GL_STATIC_DRAW);

	// Initialize Keyboard
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

	// Compile and load shaders
	GLuint programID = LoadShaders("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

	do {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClearDepth(GL_DEPTH_BUFFER_BIT);

		// Render
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Use shader
		glUseProgram(programID);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		// Swap Buffers
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	} while (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_Window) == 0);
}