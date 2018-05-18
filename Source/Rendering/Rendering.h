#ifndef RENDERER_H
#define RENDERER_H

class Camera;
class Shaders;

class Rendering
{
	Shaders* m_pShaders;
	GLuint m_ProgramID, m_MatrixID, m_ModelMatID, m_ViewMatID, m_TextureID, m_MV3x3MatID;
	GLFWwindow* m_pWindow;
	map<string, GLuint> m_Handles;

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
};

#endif