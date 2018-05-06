#include "HorsemanStd.h"
#include "Camera.h"

#include "Input/Input.h"

Camera::Camera() {
}

Camera::~Camera()
{
}

void Camera::Init(GLFWwindow* window) {
	m_Speed = 3.0f;
	m_Target = vec3(0, 0, 0);
	m_Position = vec3(0, 1, 13);
	m_Up = vec3(0, 1, 0);
	m_FOV = FOV - 5 * Input::Instance()->Scroll;
	m_Zoom = 1;


	auto func = [](GLFWwindow* w, double x, double y) {
		static_cast<Camera*>(glfwGetWindowUserPointer(w))->Zoom(w, x, y);
	};

	glfwSetScrollCallback(window, func);
}

void Camera::Update(GLFWwindow* window, float dt) {
	// Calculate forward vector
	MouseAngle angles = Input::Instance()->Angles;

	vec3 forward = vec3(
		glm::cos(angles.pitch) * glm::sin(angles.yaw),
		glm::sin(angles.pitch),
		glm::cos(angles.pitch) * glm::cos(angles.yaw)
	);

	// Calculate right vector
	vec3 right = vec3(
		glm::sin(angles.yaw - M_PI / 2.0f),
		0,
		glm::cos(angles.yaw - M_PI / 2.0f)
	);

	// Strafe forward
	if (Input::IsKeyPressed(window, GLFW_KEY_W) || Input::IsKeyPressed(window, GLFW_KEY_UP)) {
		m_Position += forward * dt * m_Speed;
	}

	// Strafe back
	if (Input::IsKeyPressed(window, GLFW_KEY_S) || Input::IsKeyPressed(window, GLFW_KEY_DOWN)) {
		m_Position -= forward * dt * m_Speed;
	}

	// Strafe left
	if (Input::IsKeyPressed(window, GLFW_KEY_A) || Input::IsKeyPressed(window, GLFW_KEY_LEFT)) {
		m_Position -= right * dt *m_Speed;
	}

	// Strafe right
	if (Input::IsKeyPressed(window, GLFW_KEY_D) || Input::IsKeyPressed(window, GLFW_KEY_RIGHT)) {
		m_Position += right * dt * m_Speed;
	}

	// Fly up
	if (Input::IsKeyPressed(window, GLFW_KEY_SPACE)) {
		m_Position += vec3(0, 1, 0) * dt * m_Speed;
	}

	// Fly down
	if (Input::IsKeyPressed(window, GLFW_KEY_LEFT_SHIFT)) {
		m_Position -= vec3(0, 1, 0) * dt * m_Speed;
	}

	// Calculate up and view target
	m_Up = cross(right, forward);
	m_Target = m_Position + forward;

	// Adjust FOV
	m_FOV = FOV - 5 * Input::Instance()->Scroll;
}

void Camera::Cleanup()
{
}

void Camera::Zoom(GLFWwindow* window, double xoffset, double yoffset) {
	Input::Instance()->Scroll = (int)yoffset;
}