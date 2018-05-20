#ifndef RENDERER_H
#define RENDERER_H

class Camera;
class Shader;

class Rendering
{
	GLFWwindow* m_pWindow;
	map<string, Shader*> m_Shaders;

public:
	Rendering();
	~Rendering();
	int Init(const char* title);
	int LoadContent();
	bool RegisterShader(const char* program, const char* vertexPath, const char* fragmentPath);
	void Begin();
	void End();
	void Cleanup();
	void SetWindowTitle(const char* title);
	map<string, Shader*> Shaders();

	READONLY_PROPERTY(GLFWwindow*, Window);
	GET(Window) { return m_pWindow; }		
};

#endif