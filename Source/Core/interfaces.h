#pragma once

#include <memory>

class Actor;
class ActorComponent;

typedef unsigned int ActorId;

const ActorId INVALID_ACTOR_ID = 0;

typedef std::shared_ptr<Actor> StrongActorPtr;