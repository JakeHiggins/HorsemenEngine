#ifndef GAME_H
#define GAME_H

#include <Core/HorsemanGame.h>

#include <Msvc/HorsemanStd.h>

class Camera;
class MeshComponent;

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
	void AddModel(vec3 position, const char* modelPath, const char* texturePath);

private:
	Camera * m_pCamera;
	vector<MeshComponent*> m_Models;
};

#endif#pragma once
