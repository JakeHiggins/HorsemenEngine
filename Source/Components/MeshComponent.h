#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "Actors/ActorComponent.h"
#include "rapidxml/rapidxml.hpp"

class Camera;
class Texture;
class Shader;

class MeshComponent : public ActorComponent
{
	GLuint m_VertexArrayID, m_VertexBuffer, m_UVBuffer, m_NormalBuffer, m_IndexBuffer, m_TangentBuffer, m_BitangentBuffer;
	vector<vec3> m_Vertices, m_Normals, m_Tangents, m_Bitangents;
	vector<vec2> m_UVs;
	vector<unsigned short> m_Indices;
	Texture* m_pTexture, *m_pNormal;
	bool m_RenderNormal;
	char* m_TexturePath, *m_NormalPath, *m_MeshPath, *m_Shader;

public:
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	MeshComponent();
	~MeshComponent();

	virtual bool VInit(rapidxml::xml_node<>* pNode);
	virtual void VPostInit();
	virtual void VUpdate(float dt);
	virtual void VRender(map<string, Shader*> shaders, Camera* cam, vec3 lightPos);

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

