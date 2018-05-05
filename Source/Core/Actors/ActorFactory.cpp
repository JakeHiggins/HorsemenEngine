#include "../Msvc/HorsemanStd.h"
#include "ActorFactory.h"
//
////#include "Actor.h"
////#include "ActorComponent.h"
//#include <iostream>
//#include <map>
//#include <string>
//#include <boost/shared_ptr.hpp>
//#include "rapidxml/rapidxml.hpp"
//
//
//StrongActorPtr ActorFactory::CreateActor(const char * actorResource) {
//	// Read xml file into a vector
//	std::ifstream resourceStream(actorResource);
//	if (resourceStream.is_open()) {
//
//	}
//	else {
//		printf("[Actor Resource ERROR (%s)]: Could not load file\n", actorResource);
//		getchar();
//		return nullptr;
//	}
//
//	std::vector<char> std::buffer((std::istreambuf_iterator<char>(resourceStream)), std::istreambuf_iterator<char>());
//	buffer.push_back('\0');
//
//	StrongActorPtr pActor(new Actor(GetNextActorId()));
//
//	// Parse buffer using rapidxml
//	try {
//		rapidxml::xml_document<> doc;
//		rapidxml::xml_node<>* pRoot;
//		doc.parse<0>(&buffer[0]);
//
//		// Find root node
//		pRoot = doc.first_node("Actor");
//
//		// Loop through components
//		for (rapidxml::xml_node<>* cnode = pRoot->first_node();
//			cnode; cnode = cnode->next_sibling()) {
//			cout << cnode->name() << endl;
//
//			CreateComponent(cnode);
//
//			cout << "\n" << endl;
//		}
//	}
//	catch (const std::runtime_error& e)
//	{
//		printf("[Actor Resource ERROR (%s)]: Runtime error %s\n", actorResource, e.what());
//		return nullptr;
//	}
//	catch (const rapidxml::parse_error& e)
//	{
//		printf("[Actor Resource ERROR (%s)]: Parse error %s\n", actorResource, e.what());
//		return nullptr;
//	}
//	catch (const std::exception& e)
//	{
//		printf("[Actor Resource ERROR (%s)]: General error %s\n", actorResource, e.what());
//		return nullptr;
//	}
//	catch (int e) {
//		printf("[Actor Resource ERROR (%s)]: Unknown error occured\n", actorResource);
//		return nullptr;
//	}
//
//	return pActor;
//}
//
////StrongActorComponentPtr ActorFactory::CreateComponent(rapidxml::xml_node<>* cnode) {
////	// Loop through variables inside components
////	for (rapidxml::xml_node<>* cvar = cnode->first_node();
////		cvar; cvar = cvar->next_sibling()) {
////
////		cout << cvar->name() << endl;
////
////		// Loop through parameters of component variable
////		for (rapidxml::xml_attribute<>* cattr = cvar->first_attribute();
////			cattr; cattr = cattr->next_attribute()) {
////			cout << cattr->name() << " = " << cattr->value() << endl;
////		}
////	}
////
////	return nullptr;
////}
//
//ActorId ActorFactory::GetNextActorId() {
//	m_LastActorId++;
//	return m_LastActorId;
//}