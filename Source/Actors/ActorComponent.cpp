#include "HorsemanStd.h"
#include "ActorComponent.h"

#include <iostream>

bool ActorComponent::Init(rapidxml::xml_node<>* pNode)
{
	// Loop through variables inside components
	for (rapidxml::xml_node<>* cvar = pNode->first_node();
		cvar; cvar = cvar->next_sibling()) {

		std::cout << cvar->name() << std::endl;

		// Loop through parameters of component variable
		for (rapidxml::xml_attribute<>* cattr = cvar->first_attribute();
			cattr; cattr = cattr->next_attribute()) {
			std::cout << cattr->name() << " = " << cattr->value() << std::endl;
		}
	}
	return true;
}
