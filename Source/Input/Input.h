#ifndef INPUT_H
#define INPUT_H

struct MouseAngle {
	float yaw, pitch;
};

class Input
{
	static Input* m_pInstance;
	MouseAngle m_Angles;
	float m_MouseSpeed;
	int m_Scroll;

public:
	static Input* Instance();
	static GLuint IsKeyPressed(GLuint key);
	static GLuint IsKeyPressed(GLFWwindow* window, GLuint key);
	void Init(GLFWwindow* window);
	void Update(GLFWwindow* window, float dt);

	READONLY_PROPERTY(MouseAngle, Angles);
	GET(Angles) { return m_Angles; };

	PROPERTY(int, Scroll);
	GET(Scroll) { return m_Scroll; }
	SET(Scroll) { m_Scroll = value; }

private:
	Input();
	Input(Input const&);
	~Input();
	Input& operator=(Input const&);
	
};

#endif