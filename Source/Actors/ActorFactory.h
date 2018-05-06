#ifndef ACTORFACTORY_H
#define ACTORFACTORY_H

typedef ActorComponent* (__stdcall *ActorComponentCreator)(void);
typedef map<string, ActorComponentCreator> ActorComponentCreatorMap;

class ActorFactory {
	ActorId m_LastActorId;

protected:
	//GenericObjectFactory<ActorComponent> m_ComponentFactory
	ActorComponentCreatorMap m_ActorComponentCreators;

public:
	ActorFactory();

	StrongActorPtr CreateActor(const char* actorResource);

protected:
	virtual StrongActorComponentPtr CreateComponent(rapidxml::xml_node<>* pNode, const char* actorResource); 

private:
	ActorId GetNextActorId();

	/*ActorComponent* CreateTransformComponent() {
		return new TransformComponent();
	}*/
};

#endif