#ifndef GAME_H
#define GAME_H

#include <Core/HorsemanGame.h>

#include <Msvc/HorsemanStd.h>

class Camera;
class MeshComponentOld;
class ActorFactory;
class Font;

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
	Font* m_pFont;
	vector<StrongActorPtr> m_Actors;
	float m_Min, m_Max;
	vec3 m_Forward1, m_Forward2, m_Forward3;
	int m_Target;
};

#endif#pragma once
