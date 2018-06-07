#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include "Actors/ActorComponent.h"

class Texture;
class Shader;

class LightComponent : public ActorComponent {
	vec3 m_Position, m_Color;
	float m_Intensity;

public:
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	LightComponent();
	~LightComponent();

	virtual bool VInit(rapidxml::xml_node<>* pNode);
	virtual void VPostInit();
	virtual void VUpdate(float dt);
	virtual void VRender(Camera* cam, vec3 lightPos);

	void Cleanup();

	static ActorComponent* __stdcall Create() { return new LightComponent(); }
};

#endif