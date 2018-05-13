#include "Game.h"

#include <Actors/ActorFactory.h>
#include <Actors/Actor.h>
#include <Components/Camera.h>
#include <Components/MeshComponent.h>
#include <Components/TransformComponent.h>
#include <Input/Input.h>
#include <Rendering/Rendering.h>
#include <Rendering/Texture.h>

#include <iostream>
#include <fstream>

Game::Game() : HorsemanGame()
{
	m_pCamera = new Camera();
	m_Actors = vector<StrongActorPtr>();
	m_Min = -5.0f;
	m_Max = 5.0f;
	m_Target = 0;
	m_Forward1 = vec3(0.001f, 0, 0);
	m_Forward2 = vec3(0, 0.001f, 0);
	m_Forward3 = vec3(0, 0, 0.001f);
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
	ActorFactory factory = ActorFactory();
	AddActor(factory, "../../Assets/Actors/cube.xml");
	AddActor(factory, "../../Assets/Actors/statue.xml");
	AddActor(factory, "../../Assets/Actors/torus.xml");
}

void Game::Update(float dt) {
	Renderer->Update(dt);
	Input::Instance()->Update(Renderer->Window, dt);
	m_pCamera->Update(Renderer->Window, dt);

	shared_ptr<TransformComponent> transform1 = MakeStrongPtr(m_Actors[0]->GetComponent<TransformComponent>(TransformComponent::g_Name));
	shared_ptr<TransformComponent> transform2 = MakeStrongPtr(m_Actors[1]->GetComponent<TransformComponent>(TransformComponent::g_Name));
	shared_ptr<TransformComponent> transform3 = MakeStrongPtr(m_Actors[2]->GetComponent<TransformComponent>(TransformComponent::g_Name));

	if (transform2->Translation.x >= m_Max) {
		m_Forward1.x = -0.001f;
	}
	else if (transform2->Translation.x <= m_Min) {
		m_Forward1.x = 0.001f;
	}

	if (transform1->Scalar.y >= m_Max/4) {
		m_Forward2.y = -0.001f;
	}
	else if (transform1->Scalar.y <= m_Min/4) {
		m_Forward2.y = 0.001f;
	}

	if (transform3->Translation.z >= m_Max) {
		m_Forward3.z = -0.001f;
	}
	else if (transform3->Translation.z <= m_Min) {
		m_Forward3.z = 0.001f;
	}

	transform1->Scale(m_Forward2);
	transform2->Move(m_Forward1);
	transform3->Rotate(m_Forward3);
	
}

void Game::Render() {
	Renderer->Begin();

	for (auto actor : m_Actors) {
		actor->Render(Renderer->Handles(), m_pCamera, vec3(4, 4, 4));
	}

	Renderer->End();
}

void Game::Cleanup() {
	for (auto actor : m_Actors) {
		actor->Cleanup();
	}

	m_pCamera->Cleanup();
	SAFE_DELETE(m_pCamera);

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

	shared_ptr<MeshComponent> mesh = MakeStrongPtr(actor->GetComponent<MeshComponent>(MeshComponent::g_Name));
	std::cout << "Mesh Component added with texture path: " << mesh->TexturePath << std::endl;
	std::cout << "Mesh Component added with mesh path: " << mesh->MeshPath << std::endl;

	Renderer->LoadShader("ProgramID", "../../Assets/Shaders/vertex_shader.glsl", "../../Assets/Shaders/fragment_shader.glsl");
	Renderer->LoadContent();

	m_Actors.push_back(actor);
}