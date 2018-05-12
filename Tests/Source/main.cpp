#include "Game.h"

int main() {
	Game* game = new Game();

	game->Init();
	game->LoadContent();

	double lastTime = glfwGetTime();
	double lastTimer = glfwGetTime();
	int nbFrames = 0;
	do {
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTimer >= 1.0) {
			printf("%f ms/frame\n", 1000 / double(nbFrames));
			printf("%i FPS\n", nbFrames);
			nbFrames = 0;
			lastTimer += 1;
		}

		float dt = float(currentTime - lastTime);

		game->Update(dt);
		game->Render();

		lastTime = currentTime;
	} while (game->Active());

	game->Cleanup();

	return 0;
}