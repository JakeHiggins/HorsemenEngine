#include "Input.h"
#include "Graphics.h"

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

void Input::Init(GLFWwindow* window) {
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

GLuint Input::IsKeyPressed(GLuint key) {
	GLFWwindow* window = Graphics::Instance()->Window;

	return glfwGetKey(window, key) == GLFW_PRESS;
}

GLuint Input::IsKeyPressed(GLFWwindow * window, GLuint key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

void Input::Update(float dt) {
	double xpos, ypos;
	glfwGetCursorPos(Graphics::Instance()->Window, &xpos, &ypos);

	glfwSetCursorPos(Graphics::Instance()->Window, WIDTH / 2, HEIGHT / 2);

	m_Angles.yaw += m_MouseSpeed * dt * float(WIDTH / 2 - xpos);
	m_Angles.pitch += m_MouseSpeed * dt * float(HEIGHT / 2 - ypos);
}