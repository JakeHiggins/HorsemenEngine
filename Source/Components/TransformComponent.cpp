#include "HorsemanStd.h"
#include "TransformComponent.h"

const char* TransformComponent::g_Name = "TransformComponent";

bool TransformComponent::VInit(rapidxml::xml_node<>* pNode)
{
	return true;
}

void TransformComponent::VPostInit()
{
}

void TransformComponent::VUpdate(float dt)
{
}
