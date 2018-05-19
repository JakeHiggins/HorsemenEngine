#include "HorsemanStd.h"
#include "Actor.h"
#include "ActorComponent.h"
#include "Components/Camera.h"
#include "Rendering/Shader.h"
#include <iostream>

Actor::Actor(ActorId id) {
	m_Id = id;
}

Actor::~Actor(void) {
}

bool Actor::Init(rapidxml::xml_node<>* pNode) {
	return true;
}

void Actor::PostInit() {	
	for (auto comp : m_Components) {
		auto pComp = comp.second;
		pComp->VPostInit();
	}
}

void Actor::Cleanup(void)
{
	m_Components.clear();
}

void Actor::Update(float dt)
{
	for (auto comp : m_Components) {
		auto pComp = comp.second;
		pComp->VUpdate(dt);
	}
}

void Actor::Render(map<string, Shader*> shaders, Camera * cam, vec3 lightPos) {
	for (auto comp : m_Components) {
		auto pComp = comp.second;
		pComp->VRender(shaders, cam, lightPos);
	}
}

void Actor::AddComponent(StrongActorComponentPtr pComponent) {
	m_Components[pComponent->VGetId()] = pComponent;
}
