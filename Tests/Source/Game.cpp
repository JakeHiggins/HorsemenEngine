#include "Game.h"

#include <Actors/ActorFactory.h>
#include <Actors/Actor.h>
#include <Components/Camera.h>
#include <Components/MeshComponent.h>
#include <Components/TransformComponent.h>
#include <Input/Input.h>
#include <Rendering/Rendering.h>

#include <iostream>

Game::Game() : HorsemanGame()
{
	m_pCamera = new Camera();
	m_Models = vector<MeshComponent*>();
	ActorFactory f = ActorFactory();
	StrongActorPtr actor = f.CreateActor("../../Assets/Actors/test.xml");
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
}

Game::~Game()
{
}

void Game::Init() {
	HorsemanGame::Init("Game 1");
	Input::Instance()->Init(Renderer->Window);
	m_pCamera->Init(Renderer->Window);
}

void Game::LoadContent() {
	Renderer->LoadShader("ProgramID", "../../Assets/Shaders/vertex_shader.glsl", "../../Assets/Shaders/fragment_shader.glsl");
	Renderer->LoadContent();

	AddModel(vec3(0, -3, 0), "../../Assets/Models/statue.obj", "../../Assets/Textures/statue/statue_dd.dds");
	AddModel(vec3(7, 0, 0), "../../Assets/Models/torus.obj", "../../Assets/Textures/white_d.dds");
	AddModel(vec3(-5, 0, 0), "../../Assets/Models/cube.obj", "../../Assets/Textures/obsidian_d.dds");
}

void Game::Update(float dt) {
	Renderer->Update(dt);
	Input::Instance()->Update(Renderer->Window, dt);
	m_pCamera->Update(Renderer->Window, dt);
}

void Game::Render() {
	Renderer->Begin();

	for (auto &model : m_Models) {
		model->Render(Renderer->Handles(), m_pCamera, vec3(4, 4, 4));
	}

	Renderer->End();
}

void Game::Cleanup() {
	for (auto &model : m_Models) {
		model->Cleanup();
		SAFE_DELETE(model);
	}

	m_pCamera->Cleanup();
	SAFE_DELETE(m_pCamera);

	HorsemanGame::Cleanup();
}

void Game::AddModel(vec3 position, const char * modelPath, const char* texturePath)
{
	MeshComponent* m = new MeshComponent(position);
	m->Init();
	m->LoadContent(modelPath, texturePath);
	m_Models.push_back(m);
}
