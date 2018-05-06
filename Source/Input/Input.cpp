#include "HorsemanStd.h"
#include "Input.h"

Input* Input::m_pInstance = NULL;

Input* Input::Instance() {
	if (!m_pInstance)
		m_pInstance = new Input();

	return m_pInstance;
}

Input::Input() {
	m_Angles = MouseAngle();
	m_Angles.yaw = 3.14f;
	m_Angles.pitch = 0;

	m_MouseSpeed = 2.0f;
	m_Scroll = 1;
}

Input::~Input()
{
	SAFE_DELETE(m_pInstance)
}

void Input::Init(GLFWwindow* window) {
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

GLuint Input::IsKeyPressed(GLFWwindow * window, GLuint key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

void Input::Update(GLFWwindow * window, float dt) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);

	m_Angles.yaw += m_MouseSpeed * dt * float(WIDTH / 2 - xpos);
	m_Angles.pitch += m_MouseSpeed * dt * float(HEIGHT / 2 - ypos);
}