#ifndef GAME_H
#define GAME_H

#include <Core/HorsemanGame.h>

#include <Msvc/HorsemanStd.h>

class Camera;
class ActorFactory;
class Font;

class Game : public HorsemanGame {
	Camera * m_pCamera;
	Font* m_pFont;
	vector<StrongActorPtr> m_Actors;

public:
	Game();
	virtual ~Game();
	void Init();
	void LoadContent();
	void Update(float dt);
	void Render();
	void Cleanup();

	// Frames Per Second and Milliseconds Per Frame
	int FPS;
	double MSPF;

private:
	void AddActor(ActorFactory factory, const char* actorResource);
};

#endif
