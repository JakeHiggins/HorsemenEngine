#ifndef MODEL_H
#define MODEL_H
#include <map>

#include "properties.h"
#include "cube.h"
#include "Texture.h"
#include "Camera.h"
#include "Input.h"
#include "Utils/loaders.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

class Model
{
public:
	Model(vec3 position);
	~Model();

	void Init();
	void LoadContent(const char* model, const char* texture);
	void Update(float dt);
	// void Render(GLuint programID, GLuint textureID, GLuint matrixID, GLuint modelMatID, GLuint viewMatID, Camera* camera);
	void Render(map<string, GLuint> handles, Camera* cam, vec3 lightPos);
	void Cleanup();

	READONLY_PROPERTY(mat4, Transform);
	GET(Transform) { return m_Transform; };

private:
	/*void translate(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotate(float yaw, float pitch, float roll);*/

	GLuint m_VertexArrayID, m_VertexBuffer, m_UVBuffer, m_NormalBuffer;
	mat4 m_Transform;
	vec3 m_Position, m_Rotation, m_Scale;
	vector<vec3> m_Vertices, m_Normals;
	vector<vec2> m_UVs;
	Texture* m_Texture;
	int m_Mode = 0;
};

#endif

