#ifndef MODEL_H
#define MODEL_H

#include "../Rendering/Texture.h"
#include "Camera.h"
#include "../Input.h"
#include "../Utils/loaders.h"
#include "../Utils/properties.h"

#include <map>

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
	void Render(map<string, GLuint> handles, Camera* cam, vec3 lightPos);
	void Cleanup();

	READONLY_PROPERTY(mat4, Transform);
	GET(Transform) { return m_Transform; };

private:

	GLuint m_VertexArrayID, m_VertexBuffer, m_UVBuffer, m_NormalBuffer;
	mat4 m_Transform;
	vec3 m_Position, m_Rotation, m_Scale;
	vector<vec3> m_Vertices, m_Normals;
	vector<vec2> m_UVs;
	Texture* m_pTexture;
	int m_Mode = 0;
};

#endif

