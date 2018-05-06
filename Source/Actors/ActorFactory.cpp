#include "HorsemanStd.h"
#include "ActorFactory.h"

#include "Actor.h"
#include "ActorComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include <iostream>
#include <fstream>


ActorFactory::ActorFactory()
{
	m_ActorComponentCreators["TransformComponent"] = &TransformComponent::Create;
	m_ActorComponentCreators["MeshComponent"] = &MeshComponent::Create;
}

StrongActorPtr ActorFactory::CreateActor(const char * actorResource) {
	// Read xml file into a vector
	//std::ifstream resourceStream(actorResource);
	std::ifstream resourceStream(actorResource);
	if (!resourceStream.is_open()) {
		printf("[Actor Resource ERROR (%s)] Could not load file\n", actorResource);
		getchar();
		return nullptr;
	}

	std::vector<char> buffer((std::istreambuf_iterator<char>(resourceStream)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	StrongActorPtr pActor(new Actor(GetNextActorId()));

	if (!pActor->Init()) {
		printf("[ActorFactory ERROR (%s)] Actor failed to initialize\n", actorResource);
		return StrongActorPtr();
	}

	// Parse buffer using rapidxml
	try {
		rapidxml::xml_document<> doc;
		rapidxml::xml_node<>* pRoot;
		doc.parse<0>(&buffer[0]);

		// Find root node
		pRoot = doc.first_node("Actor");

		// Loop through components
		for (rapidxml::xml_node<>* pNode = pRoot->first_node();
			pNode; pNode = pNode->next_sibling()) {
			std::cout << pNode->name() << std::endl;

			StrongActorComponentPtr pComponent(CreateComponent(pNode, actorResource));
			if (pComponent) {
				pActor->AddComponent(pComponent);
				pComponent->SetOwner(pActor);
			}
			else {
				printf("[ActorFactory ERROR (%s)] Component failed to load: %s\n", actorResource, pNode->name());
				return StrongActorPtr();
			}

			std::cout << "\n" << std::endl;
		}
	}
	catch (const std::runtime_error& e)
	{
		printf("[Actor Resource ERROR (%s)] Runtime error: %s\n", actorResource, e.what());
		return StrongActorPtr();
	}
	catch (const rapidxml::parse_error& e)
	{
		printf("[Actor Resource ERROR (%s)] Parse error: %s\n", actorResource, e.what());
		return StrongActorPtr();
	}
	catch (const std::exception& e)
	{
		printf("[Actor Resource ERROR (%s)] General error: %s\n", actorResource, e.what());
		return StrongActorPtr();
	}
	catch (int e) {
		printf("[Actor Resource ERROR (%s)] Unknown error occured\n", actorResource);
		return StrongActorPtr();
	}

	pActor->PostInit();
	return pActor;
}

ActorId ActorFactory::GetNextActorId() {
	m_LastActorId++;
	return m_LastActorId;
}

StrongActorComponentPtr ActorFactory::CreateComponent(rapidxml::xml_node<>* pNode, const char* actorResource) {
	string name = pNode->name();

	StrongActorComponentPtr pComponent;

	auto findIt = m_ActorComponentCreators.find(name);
	if (findIt != m_ActorComponentCreators.end()) {
		ActorComponentCreator creator = findIt->second;
		pComponent.reset(creator());
	}
	else {
		printf("[ActorFactory ERROR (%s)] Could not find ActorComponent: %s\n", actorResource, name.c_str());
		return StrongActorComponentPtr();
	}

	// Initialize component
	if (pComponent) {
		if (!pComponent->Init(pNode)) {
			printf("[ActoryFactory ERROR (%s)] Component failed to initialize: %s\n", actorResource, name.c_str());
			return StrongActorComponentPtr();
		}
	}

	return pComponent;
}