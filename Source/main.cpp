#include "HorsemanStd.h"
#include "Core/HorsemanGame.h"

int main() {
	HorsemanGame* game = new HorsemanGame();

	game->Init("Internal Test");

	//ActorFactory f = ActorFactory();
	//f.CreateActor("Assets/Actors/test.xml");

	double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	do {
		currentTime = glfwGetTime();
		float dt = float(currentTime - lastTime);

		lastTime = currentTime;
	} while (game->Active());

	game->Cleanup();

	return 0;
}