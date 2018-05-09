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
	//void AddModel(vec3 position, const char* modelPath, const char* texturePath);
	void AddActor(ActorFactory factory, const char* actorResource);

private:
	Camera * m_pCamera;
	//vector<MeshComponentOld*> m_Models;
	vector<StrongActorPtr> m_Actors;
	//StrongActorPtr m_Actor;
	float m_DemoRadius;
	float m_DemoAngle;
};

#endif#pragma once
