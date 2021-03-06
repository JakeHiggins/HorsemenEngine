#include "Game.h"

#include <Actors/ActorFactory.h>
#include <Actors/Actor.h>
#include <Components/Camera.h>
#include <Components/MeshComponent.h>
#include <Components/TransformComponent.h>
#include <Input/Input.h>
#include <Rendering/Font.h>
#include <Rendering/Rendering.h>
#include <Rendering/Texture.h>

#include <iostream>
#include <fstream>

Game::Game() : HorsemanGame()
{
	m_pCamera = new Camera();
	m_Actors = vector<StrongActorPtr>();
	m_pFont = new Font();
}

Game::~Game()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pFont);
}

void Game::Init() {
	HorsemanGame::Init("horseman_config.txt", "Horseman Tests");
	Input::Instance()->Init(Renderer->Window);
	m_pCamera->Init(Renderer->Window);
}

void Game::LoadContent() {
	ActorFactory factory = ActorFactory();
	AddActor(factory, "../../Assets/Actors/cube.xml");
	AddActor(factory, "../../Assets/Actors/statue.xml");
	AddActor(factory, "../../Assets/Actors/torus.xml");
	//AddActor(factory, "../../Assets/Actors/lightbulb.xml");
	AddActor(factory, "../../Assets/Actors/glass.xml");

	m_pFont->LoadFont("consolas");
}

void Game::Update(float dt) {
	Input::Instance()->Update(Renderer->Window, dt);
	m_pCamera->Update(Renderer->Window, dt);
}

void Game::Render() {
	Renderer->Begin();

	for (auto actor : m_Actors) {
		actor->Render(m_pCamera, vec3(0, 6, 0));
	}

	m_pFont->Print(std::to_string(FPS).c_str(), 5, 700, 32);

	Renderer->End();
}

void Game::Cleanup() {
	for (auto actor : m_Actors) {
		actor->Cleanup();
	}

	m_pCamera->Cleanup();
	m_pFont->Cleanup();

	HorsemanGame::Cleanup();
}

void Game::AddActor(ActorFactory factory, const char* actorResource) {
	StrongActorPtr actor = factory.CreateActor(actorResource);
	if (actor == nullptr) {
		std::printf("[ActorFactory ERROR] something went wrong\n\n");
		return;
	}
	else {
		std::printf("[ActorFactory INFO] Everything is awesome!\n\n");
	}

	// Ensure that we can get a component by name and by id
	shared_ptr<TransformComponent> cName = MakeStrongPtr(actor->GetComponent<TransformComponent>(TransformComponent::g_Name));
	shared_ptr<TransformComponent> cId = MakeStrongPtr(actor->GetComponent<TransformComponent>(4084754326));

	std::cout << "Component by name with translation: [" << cName->Translation.x << ", " << cName->Translation.y << ", " << cName->Translation.z << "]" << std::endl;
	std::cout << "Component by id with translation: [" << cId->Translation.x << ", " << cId->Translation.y << ", " << cId->Translation.z << "]" << std::endl;

	m_Actors.push_back(actor);
}