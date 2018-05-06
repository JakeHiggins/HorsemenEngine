#pragma once

class Actor;
class ActorComponent;

typedef unsigned int ActorId;
typedef unsigned int ComponentId;

const ActorId INVALID_ACTOR_ID = 0;


typedef shared_ptr<Actor> StrongActorPtr;
typedef shared_ptr<ActorComponent> StrongActorComponentPtr;