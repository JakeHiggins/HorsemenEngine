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
	m_ActorComponentCreators[TransformComponent::g_Name] = &TransformComponent::Create;
	m_ActorComponentCreators[MeshComponent::g_Name] = &MeshComponent::Create;
}

StrongActorPtr ActorFactory::CreateActor(const char * actorResource) {
	// Read xml file into a vector
	std::ifstream resourceStream(actorResource);
	if (!resourceStream.is_open()) {
		printf("[Actor Resource ERROR (%s)] Could not load file\n", actorResource);
		return StrongActorPtr();
	}

	std::vector<char> buffer((std::istreambuf_iterator<char>(resourceStream)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');


	StrongActorPtr pActor(new Actor(GetNextActorId()));

	// Parse buffer using rapidxml
	try {
		rapidxml::xml_document<> doc;
		rapidxml::xml_node<>* pRoot;
		doc.parse<0>(&buffer[0]);

		// Find root node
		pRoot = doc.first_node("Actor");

		if (!pActor->Init(pRoot)) {
			printf("[ActorFactory ERROR (%s)] Actor failed to initialize\n", actorResource);
			GracefulFail();
		}

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
				return GracefulFail();
			}

			std::cout << "\n" << std::endl;
		}

		pActor->PostInit();
	}
	catch (const std::runtime_error& e)
	{
		printf("[Actor Resource ERROR (%s)] Runtime error: %s\n", actorResource, e.what());
		return GracefulFail();
	}
	catch (const rapidxml::parse_error& e)
	{
		printf("[Actor Resource ERROR (%s)] Parse error: %s\n", actorResource, e.what());
		return GracefulFail();
	}
	catch (const std::exception& e)
	{
		printf("[Actor Resource ERROR (%s)] General error: %s\n", actorResource, e.what());
		return GracefulFail();
	}
	catch (int e) {
		printf("[Actor Resource ERROR (%s)] Unknown error occured {ErrorCode: %i}\n", actorResource, e);
		return GracefulFail();
	}
	return pActor;
}

ActorId ActorFactory::GetNextActorId() {
	m_LastActorId++;
	return m_LastActorId;
}

StrongActorPtr ActorFactory::GracefulFail() {
	m_LastActorId--;
	return StrongActorPtr();
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
		if (!pComponent->VInit(pNode)) {
			printf("[ActoryFactory ERROR (%s)] Component failed to initialize: %s\n", actorResource, name.c_str());
			return StrongActorComponentPtr();
		}
	}

	return pComponent;
}