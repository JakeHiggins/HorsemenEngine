#ifndef ACTORCOMPONENT_H
#define ACTORCOMPONENT_H

#include "Actor.h"

class ActorComponent {
	friend class ActorFactory;

protected:
	StrongActorPtr m_pOwner;

public:
	virtual ~ActorComponent(void) { m_pOwner.reset(); }

	virtual bool VInit(rapidxml::xml_node<>* pNode) = 0;
	virtual void VPostInit() { }
	virtual void VUpdate(float dt) { }
	virtual void VRender(Camera* cam, vec3 lightPos) { }

	virtual ComponentId VGetId(void) const {
		string str(VGetName());
		return (ComponentId)std::hash<string>{}(str);
	};
	virtual const char* VGetName() const = 0;

private:
	void SetOwner(StrongActorPtr pOwner) { m_pOwner = pOwner; }
};

#endif