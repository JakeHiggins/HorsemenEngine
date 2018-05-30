#include "HorsemanStd.h"
#include "HorsemanGame.h"

#include "Rendering/Rendering.h"
#include "Input/Input.h"

HorsemanGame::HorsemanGame() {
	Renderer = new Rendering();
}

HorsemanGame::~HorsemanGame() {
}

void HorsemanGame::Init(const char* configPath, const char* title) {
	bool result = config.LoadHorsemanConfig(configPath);
	if (!result) { return; }
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