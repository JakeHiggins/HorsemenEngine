#ifndef GAME_H
#define GAME_H

#include "Rendering/Graphics.h"
#include "Input.h"

class Game
{
public:
	Game();
	~Game();
	void Init();
	void LoadContent();
	void Update(float dt);
	void Render();
	void Cleanup();
	bool Active();

private:
	Camera* cam;
};

#endif