#include "Graphics.h"

Graphics* Graphics::m_pInstance = NULL;

Graphics* Graphics::Instance() {
	if (!m_pInstance)
		m_pInstance = new Graphics();

	return m_pInstance;
}

Graphics::Graphics() {
	m_pShaders = new Shaders();
}

int Graphics::Init() {
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
	m_Window = glfwCreateWindow((int)WIDTH, (int)HEIGHT, "Horsemen Engine", NULL, NULL);
	if (m_Window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_Window);
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
	//glEnable(GL_CULL_FACE);

	return 1;
}

int Graphics::LoadContent() {
	m_Texture = new Texture();
	//m_Texture->LoadBMP("..\\..\\..\\Assets\\Textures\\test.bmp");
	m_Texture->LoadDDS("..\\..\\..\\Assets\\Textures\\grass.dds");

	// Create VAO
	m_VertexArrayID;
	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	m_VertexBuffer;
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_1_buffer), g_cube_1_buffer, GL_STATIC_DRAW);

	m_UVBuffer;
	glGenBuffers(1, &m_UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	// Compile and load shaders
	m_ProgramID = m_pShaders->LoadShaders("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

	// Load MVP matrix
	m_MatrixID = glGetUniformLocation(m_ProgramID, "MVP");

	m_TextureID = glGetUniformLocation(m_ProgramID, "textureSampler");

	return 1;
}

void Graphics::CalculateMVP(Camera* cam) {
	glm::mat4 Projection = cam->Projection;

	glm::mat4 Model = glm::mat4(1.0f);

	m_MVP = Projection * cam->View * Model;
}

int Graphics::Render(Camera* cam) {
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use shader
	glUseProgram(m_ProgramID);

	// Update and send MVP
	CalculateMVP(cam);
	glUniformMatrix4fv(m_MatrixID, 1, GL_FALSE, &m_MVP[0][0]);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture->Image);
	glUniform1i(m_TextureID, 0);

	// Bind vertex array
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

	// Bind color array
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	// Swap Buffers
	glfwSwapBuffers(m_Window);
	glfwPollEvents();

	return 1;
}

void Graphics::Cleanup() {
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_UVBuffer);
	glDeleteProgram(m_ProgramID);
	glDeleteVertexArrays(1, &m_VertexArrayID);

	m_Texture->Cleanup();

	glfwTerminate();
}