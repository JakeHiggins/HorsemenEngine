#ifndef ACTORCOMPONENT_H
#define ACTORCOMPONENT_H

#include "Actor.h"

class ActorComponent {
	friend class ActorFactory;

public:
	virtual ~ActorComponent(void) {}
	virtual bool Init(rapidxml::xml_node<>* pNode);

private:
	StrongActorPtr m_pOwner;
	void SetOwner(StrongActorPtr pOwner) { m_pOwner = pOwner; }
};

#endif