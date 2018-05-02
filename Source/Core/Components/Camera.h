#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Utils/properties.h"
#include "../Utils/config.h"

#include "../Input.h"

using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();
	
	void Init();
	void Update(float dt);

	void Zoom(GLFWwindow*, double, double);

	READONLY_PROPERTY(mat4, View);
	GET(View) { return lookAt(m_Position, m_Target, m_Up); };

	READONLY_PROPERTY(mat4, Projection);
	GET(Projection) { return perspective(radians(m_FOV), WIDTH / HEIGHT, NEAR_DRAW, FAR_DRAW); };

private:
	vec3 m_Target, m_Position, m_Up;
	float m_Speed, m_FOV, m_Zoom;
};

#endif