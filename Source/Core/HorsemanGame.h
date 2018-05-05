#ifndef _HORSEMANGAME_H
#define _HORSEMANGAME_H

#include "Rendering/Rendering.h"
#include "Input.h"
#include "Utils/memory.h"
#include "Utils/properties.h"

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