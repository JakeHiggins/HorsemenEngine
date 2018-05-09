#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Actors/ActorComponent.h"

class TransformComponent : public ActorComponent {

	mat4 m_Transform;

public:
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	TransformComponent(void) { m_Transform = mat4(); }

	virtual bool VInit(rapidxml::xml_node<>* pNode);
	virtual void VPostInit();
	virtual void VUpdate(float dt);

	static ActorComponent* __stdcall Create() { return new TransformComponent(); }
};

#endif