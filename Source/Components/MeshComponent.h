#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "Actors/ActorComponent.h"

class Camera;
class Texture;

class MeshComponent : public ActorComponent
{
	GLuint m_VertexArrayID, m_VertexBuffer, m_UVBuffer, m_NormalBuffer;
	mat4 m_Transform;
	vec3 m_Position, m_Rotation, m_Scale;
	vector<vec3> m_Vertices, m_Normals;
	vector<vec2> m_UVs;
	Texture* m_pTexture;
	int m_Mode = 0;

public:
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	MeshComponent(vec3 position);
	~MeshComponent();

	virtual bool VInit(rapidxml::xml_node<>* pNode);
	virtual void VPostInit();
	virtual void VUpdate(float dt);

	void Init();
	void LoadContent(const char* model, const char* texture);
	void Update(float dt);
	void Render(map<string, GLuint> handles, Camera* cam, vec3 lightPos);
	void Cleanup();

	void SetPosition(vec3 pos);

	READONLY_PROPERTY(mat4, Transform);
	GET(Transform) { return m_Transform; };

	static ActorComponent* __stdcall Create() { return new MeshComponent(vec3(0,0,0)); }
};

#endif

