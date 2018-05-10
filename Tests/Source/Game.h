#ifndef GAME_H
#define GAME_H

#include <Core/HorsemanGame.h>

#include <Msvc/HorsemanStd.h>

class Camera;
class MeshComponentOld;
class ActorFactory;

class Game : public HorsemanGame
{
public:
	Game();
	virtual ~Game();
	void Init();
	void LoadContent();
	void Update(float dt);
	void Render();
	void Cleanup();
	void AddActor(ActorFactory factory, const char* actorResource);

private:
	Camera * m_pCamera;
	vector<StrongActorPtr> m_Actors;
	int m_Target;
};

#endif#pragma once
