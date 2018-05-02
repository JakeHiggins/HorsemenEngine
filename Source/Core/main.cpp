#include "Game.h"

int main() {
	Game* game = new Game();

	game->Init();
	game->LoadContent();

	double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	do {
		currentTime = glfwGetTime();
		float dt = float(currentTime - lastTime);

		game->Update(dt);
		game->Render();

		lastTime = currentTime;
	} while (game->Active());

	game->Cleanup();

	return 0;
}