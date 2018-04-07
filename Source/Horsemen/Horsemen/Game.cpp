#include "Game.h"

Game::Game()
{
	cam = new Camera();
}

Game::~Game()
{
}

void Game::Init() {
	Graphics::Instance()->Init();
	Input::Instance()->Init(Graphics::Instance()->Window);
	cam->Init();
}

void Game::LoadContent() {
	Graphics::Instance()->LoadContent();
}

void Game::Update(float dt) {
	Input::Instance()->Update(dt);
	cam->Update(dt);
}

void Game::Render() {
	Graphics::Instance()->Render(cam);
}

void Game::Cleanup() {
	Graphics::Instance()->Cleanup();
}

bool Game::Active() {
	return !Input::IsKeyPressed(Graphics::Instance()->Window, GLFW_KEY_ESCAPE) && glfwWindowShouldClose(Graphics::Instance()->Window) == 0;
}