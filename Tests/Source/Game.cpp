#include "Game.h"

#include <Actors/ActorFactory.h>
#include <Actors/Actor.h>
#include <Components/Camera.h>
#include <Components/MeshComponentOld.h>
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
	m_Target = 0;
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

	if (Input::Instance()->IsKeyPressed(Renderer->Window, GLFW_KEY_1)) {
		m_Target = 0;
	}
	if (Input::Instance()->IsKeyPressed(Renderer->Window, GLFW_KEY_2)) {
		m_Target = 1;
	}
	if (Input::Instance()->IsKeyPressed(Renderer->Window, GLFW_KEY_3)) {
		m_Target = 2;
	}

	if (Input::Instance()->IsKeyPressed(Renderer->Window, GLFW_KEY_I)) {
		shared_ptr<TransformComponent> transform = MakeStrongPtr(m_Actors[m_Target]->GetComponent<TransformComponent>(TransformComponent::g_Name));
		transform->Move(vec3(0, 0, -0.01f));
	}
	if (Input::Instance()->IsKeyPressed(Renderer->Window, GLFW_KEY_K)) {
		shared_ptr<TransformComponent> transform = MakeStrongPtr(m_Actors[m_Target]->GetComponent<TransformComponent>(TransformComponent::g_Name));
		transform->Move(vec3(0, 0, 0.01f));
	}

	//m_DemoAngle += 1;
	//if (m_DemoAngle == 360)
	//	m_DemoAngle = 0;

	//float rads = m_DemoAngle * DEG2RAD;

	//for (auto actor : m_Actors) {
	//	shared_ptr<TransformComponent> transform = MakeStrongPtr(actor->GetComponent<TransformComponent>(TransformComponent::g_Name));
	//	float x = transform->Origin.x + m_DemoRadius * glm::cos(rads);
	//	float y = transform->Origin.y + m_DemoRadius * glm::sin(rads);
	//	vec3 target = vec3(x, y, 0);
	//	vec3 move = transform->Translation - target;
	//	transform->Move(move);
	//	//transform->Move(vec3(0.01f, 0.01f, 0.01f));
	//}
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