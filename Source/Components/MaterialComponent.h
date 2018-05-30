#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "Actors/ActorComponent.h"

class Texture;
class Shader;

class MaterialComponent : public ActorComponent {
	Shader* m_pShader;
	map<const char*, Texture> m_Textures;
	map<const char*, string> m_ImagePaths;
	char* m_VShaderPath, *m_FShaderPath;

public:
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	MaterialComponent();
	~MaterialComponent();

	virtual bool VInit(rapidxml::xml_node<>* pNode);
	virtual void VPostInit();
	virtual void VUpdate(float dt);
	virtual void VRender(map<string, Shader*> shaders, Camera* cam, vec3 lightPos);

	void Cleanup();

	static ActorComponent* __stdcall Create() { return new MaterialComponent(); }
};

#endif