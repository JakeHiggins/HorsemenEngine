#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>

#include "properties.h"
#include "concat.h"

#include "config.h"

#include "cube.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"

#include <GLFW/glfw3.h>

class Graphics
{
	public:
		int Init();
		int LoadContent();
		int Render(Camera* cam);
		void Cleanup();

		static Graphics* Instance();

		READONLY_PROPERTY(GLFWwindow*, Window);
		GET(Window) { return m_Window; }

	private:
		Graphics();
		Graphics(Graphics const&);
		Graphics& operator=(Graphics const&);
		void CalculateMVP(Camera* cam);
		static Graphics* m_pInstance;
		Shaders* m_pShaders;
		GLuint m_VertexBuffer, m_UVBuffer, m_ProgramID, m_MatrixID, m_VertexArrayID, m_TextureID;
		GLFWwindow* m_Window;
		Texture* m_Texture;
		glm::mat4 m_MVP;
};

#endif