#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <map>

#include "properties.h"
#include "concat.h"

#include "config.h"

#include "cube.h"
#include "Model.h"
#include "Shaders.h"
#include "Camera.h"

#include <GLFW/glfw3.h>

class Graphics
{
	public:
		int Init();
		int LoadContent();
		void Update(float dt);
		int Render(Camera* cam);
		void Cleanup();

		static Graphics* Instance();

		READONLY_PROPERTY(GLFWwindow*, Window);
		GET(Window) { return m_Window; }

	private:
		Graphics();
		Graphics(Graphics const&);
		Graphics& operator=(Graphics const&);
		static Graphics* m_pInstance;
		Shaders* m_pShaders;
		GLuint m_ProgramID, m_MatrixID, m_ModelMatID, m_ViewMatID, m_TextureID;
		GLFWwindow* m_Window;
		vector<Model*> m_Models;
		map<string, GLuint> m_Handles;
};

#endif