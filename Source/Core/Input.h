#ifndef INPUT_H
#define INPUT_H

#include "Utils/properties.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

struct MouseAngle {
	float yaw, pitch;
};

class Input
{
	public:
		static Input* Instance();
		static GLuint IsKeyPressed(GLuint key);
		static GLuint IsKeyPressed(GLFWwindow* window, GLuint key);
		void Init(GLFWwindow* window);
		void Update(float dt);

		READONLY_PROPERTY(MouseAngle, Angles);
		GET(Angles) { return m_Angles; };

		PROPERTY(int, Scroll);
		GET(Scroll) { return m_Scroll; }
		SET(Scroll) { m_Scroll = value; }

	private:
		Input();
		Input(Input const&);
		Input& operator=(Input const&);
		static Input* m_pInstance;
		MouseAngle m_Angles;
		float m_MouseSpeed;
		int m_Scroll;
};

#endif