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
	// Compile and load shaders
	m_Handles["ProgramID"] = m_pShaders->LoadShaders("Source/Core/Rendering/Shaders/vertex_shader.glsl", "Source/Core/Rendering/Shaders/fragment_shader.glsl");

	// Load MVP matrix
	m_Handles["MatrixID"] = glGetUniformLocation(m_Handles["ProgramID"], "MVP");
	m_Handles["ModelMatID"] = glGetUniformLocation(m_Handles["ProgramID"], "M");
	m_Handles["ViewMatID"] = glGetUniformLocation(m_Handles["ProgramID"], "V");
	m_Handles["TextureID"] = glGetUniformLocation(m_Handles["ProgramID"], "textureSampler");

	glUseProgram(m_Handles["ProgramID"]);
	m_Handles["LightID"] = glGetUniformLocation(m_Handles["ProgramID"], "LightPosition_worldspace");

	m_Models = vector<Model*>();
	Model* m1 = new Model(vec3(0,-3,0));
	Model* m2 = new Model(vec3(7,0,0));
	Model* m3 = new Model(vec3(-5,0,0));

	m1->Init();
	m2->Init();
	m3->Init();

	m1->LoadContent("Assets/Models/statue.obj", "Assets/Textures/statue/statue_dd.dds");
	m2->LoadContent("Assets/Models/torus.obj", "Assets/Textures/white_d.dds");
	m3->LoadContent("Assets/Models/cube.obj", "Assets/Textures/obsidian_d.dds");

	m_Models.push_back(m1);
	m_Models.push_back(m2);
	m_Models.push_back(m3);

	return 1;
}

void Graphics::Update(float dt) {
	for (auto &model : m_Models) {
		model->Update(dt);
	}
}

int Graphics::Render(Camera* cam) {
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto &model : m_Models) {
		model->Render(m_Handles, cam, vec3(4, 4, 4));
	}

	// Swap Buffers
	glfwSwapBuffers(m_Window);
	glfwPollEvents();

	return 1;
}

void Graphics::Cleanup() {
	glDeleteProgram(m_ProgramID);

	for (auto &model : m_Models) {
		model->Cleanup();
	}

	glfwTerminate();
}