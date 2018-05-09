#ifndef ACTOR_H
#define ACTOR_H

class Actor {
	friend class ActorFactory;

	typedef map<ComponentId, StrongActorComponentPtr> ActorComponents;

	ActorId m_Id;
	ActorComponents m_Components;

public:
	explicit Actor(ActorId id);
	~Actor(void);

	bool Init(rapidxml::xml_node<>* pNode);
	void PostInit(void);
	void Cleanup(void);
	void Update(float dt);

	template <class ComponentType>
	weak_ptr<ComponentType> GetComponent(ComponentId id) {
		ActorComponents::iterator findIt = m_Components.find(id);
		if (findIt != m_Components.end()) {
			StrongActorComponentPtr pBase(findIt->second);

			// Cast to subclass version of the pointer
			shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));
			// Convert strong to weak pointer
			weak_ptr<ComponentType> pWeakSub(pSub);

			return pWeakSub;
		}
		else {
			return weak_ptr<ComponentType>();
		}
	}

	template <class ComponentType>
	weak_ptr<ComponentType> GetComponent(const char* name) {
		string str(name);
		ComponentId id = std::hash<string>{}(name);
		return GetComponent(id);
	}

	READONLY_PROPERTY(ActorId, Id);
	GET(Id) { return m_Id; };

private:
	void AddComponent(StrongActorComponentPtr pComponent);
};

#endif