#ifndef ACTOR_H
#define ACTOR_H

class Actor {
	friend class ActorFactory;

public:
	explicit Actor(ActorId id);
	~Actor(void);
	ActorId Id();
	bool Init();
	void PostInit();

private:
	ActorId m_Id;
	void AddComponent(StrongActorComponentPtr pComponent);
};

#endif