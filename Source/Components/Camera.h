#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
	Camera();
	~Camera();
	
	void Init(GLFWwindow* window);
	void Update(GLFWwindow* window, float dt);
	void Cleanup();

	void Zoom(GLFWwindow*, double, double);


	READONLY_PROPERTY(mat4, View);
	GET(View) { return glm::lookAt(m_Position, m_Target, m_Up); };

	READONLY_PROPERTY(mat4, Projection);
	GET(Projection) { return glm::perspective(glm::radians(m_FOV), WIDTH / HEIGHT, NEAR_DRAW, FAR_DRAW); };

private:
	vec3 m_Target, m_Position, m_Up;
	float m_Speed, m_FOV, m_Zoom;
};

#endif