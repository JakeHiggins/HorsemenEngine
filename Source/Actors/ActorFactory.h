#ifndef ACTORFACTORY_H
#define ACTORFACTORY_H
//
////typedef ActorComponent *(*ActorComponentCreator)(void);
////typedef std::map<std::string, ActorComponentCreator> ActorComponentCreatorMap;
//
//// Actor typedefs for simplicity sake
//typedef unsigned long ActorId;
//typedef boost::shared_ptr<Actor> StrongActorPtr;
////typedef boost::shared_ptr<ActorComponent> StrongActorComponentPtr;
//
class ActorFactory {
//	ActorId m_LastActorId;
//
////protected:
////	ActorComponentCreatorMap m_ActorComponentCreators;
//
public:
	ActorFactory() {}

//	StrongActorPtr CreateActor(const char* actorResource); 
//
////protected:
////	virtual StrongActorComponentPtr CreateComponent(rapidxml::xml_node<>* cnode); 
//
//private:
//	ActorId GetNextActorId();
};

#endif