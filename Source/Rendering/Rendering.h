#ifndef RENDERER_H
#define RENDERER_H

//#include <stdio.h>
//#include <stdlib.h>
//#include <map>
//
//#include "Utils/properties.h"
//#include "Utils/concat.h"
//#include "Utils/config.h"
//#include "Utils/memory.h"
//
//#include "Components/MeshComponent.h"
//#include "Shaders.h"
//#include "Components/Camera.h"
//
//#include <GLFW/glfw3.h>

class Camera;
class Shaders;

class Rendering
{
	public:
		Rendering();
		~Rendering();
		int Init(const char* title);
		int LoadContent();
		bool LoadShader(const char* program, const char* vertexPath, const char* fragmentPath);
		void Update(float dt);
		int Render(Camera* cam);
		void Begin();
		void End();
		void Cleanup();
		void SetWindowTitle(const char* title);
		map<string, GLuint> Handles();

		READONLY_PROPERTY(GLFWwindow*, Window);
		GET(Window) { return m_pWindow; }

	private:
		Shaders* m_pShaders;
		GLuint m_ProgramID, m_MatrixID, m_ModelMatID, m_ViewMatID, m_TextureID;
		GLFWwindow* m_pWindow;
		map<string, GLuint> m_Handles;
};

#endif