#ifndef _HORSEMANGAME_H
#define _HORSEMANGAME_H

class Rendering;

class HorsemanGame
{
public:
	HorsemanGame();
	virtual ~HorsemanGame();

	void Init(const char* title = "Horseman Engine Game");
	void Cleanup();
	bool Active();
	Rendering* Renderer;
};

#endif