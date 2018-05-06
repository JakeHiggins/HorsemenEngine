#include "HorsemanStd.h"
#include "Actor.h"
#include "ActorComponent.h"

Actor::Actor(ActorId id) {
	m_Id = id;
}

Actor::~Actor(void)
{
}


ActorId Actor::Id() {
	return m_Id;
}

bool Actor::Init()
{
	return true;
}

void Actor::PostInit()
{
}

void Actor::AddComponent(StrongActorComponentPtr pComponent)
{
}
