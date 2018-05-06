#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Actors/ActorComponent.h"

class TransformComponent : public ActorComponent {
public:
	TransformComponent() {}

	static ActorComponent* __stdcall Create() { return new TransformComponent; }
};

#endif