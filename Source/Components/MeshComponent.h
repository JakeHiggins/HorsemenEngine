#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "Actors/ActorComponent.h"
#include "rapidxml/rapidxml.hpp"

class Camera;
class Texture;

class MeshComponent : public ActorComponent
{
	GLuint m_VertexArrayID, m_VertexBuffer, m_UVBuffer, m_NormalBuffer;
	vector<vec3> m_Vertices, m_Normals;
	vector<vec2> m_UVs;
	Texture* m_pTexture;
	char* m_TexturePath;
	char* m_MeshPath;

public:
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	MeshComponent();
	~MeshComponent();

	virtual bool VInit(rapidxml::xml_node<>* pNode);
	virtual void VPostInit();
	virtual void VUpdate(float dt);
	virtual void VRender(map<string, GLuint> handles, Camera* cam, vec3 lightPos);

	void Cleanup();

	static ActorComponent* __stdcall Create() { return new MeshComponent(); }

	READONLY_PROPERTY(char*, TexturePath);
	GET(TexturePath) { return m_TexturePath; };

	READONLY_PROPERTY(char*, MeshPath);
	GET(MeshPath) { return m_MeshPath; };

private:
	mat4 GetTransform();
};

#endif

