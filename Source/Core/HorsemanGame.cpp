#include "HorsemanGame.h"

HorsemanGame::HorsemanGame() {
	Renderer = new Rendering();
}

HorsemanGame::~HorsemanGame() {
}

void HorsemanGame::Init(const char* title) {
	Renderer->Init(title);
}

void HorsemanGame::Cleanup() {
	Renderer->Cleanup();
	SAFE_DELETE(Renderer);
	glfwTerminate();
}

bool HorsemanGame::Active() {
	return !Input::IsKeyPressed(Renderer->Window, GLFW_KEY_ESCAPE) && glfwWindowShouldClose(Renderer->Window) == 0;
}