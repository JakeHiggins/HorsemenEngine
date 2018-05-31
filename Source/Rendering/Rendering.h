#ifndef RENDERER_H
#define RENDERER_H

class Camera;
class Shader;

class Rendering
{
	GLFWwindow* m_pWindow;

public:
	Rendering();
	~Rendering();
	int Init(const char* title);
	int LoadContent();
	void Begin();
	void End();
	void Cleanup();
	void SetWindowTitle(const char* title);

	READONLY_PROPERTY(GLFWwindow*, Window);
	GET(Window) { return m_pWindow; }		
};

#endif