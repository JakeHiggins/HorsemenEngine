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
	m_Min = -5.0f;
	m_Max = 5.0f;
	m_Target = 0;
	m_Forward1 = vec3(0, 0, 0.001f);
	m_Forward2 = vec3(0.001f, 0.001f, 0.001f);
	m_Forward3 = vec3(0, 0, 0.001f);

	m_pFont = new Font();
}

Game::~Game()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pFont);
}

void Game::Init() {
	HorsemanGame::Init("Horseman Tests");
	Input::Instance()->Init(Renderer->Window);
	m_pCamera->Init(Renderer->Window);
}

void Game::LoadContent() {
	ActorFactory factory = ActorFactory();
	AddActor(factory, "../../Assets/Actors/cube.xml");
	AddActor(factory, "../../Assets/Actors/statue.xml");
	AddActor(factory, "../../Assets/Actors/torus.xml");
	AddActor(factory, "../../Assets/Actors/lightbulb.xml");
	//AddActor(factory, "../../Assets/Actors/glass.xml");

	Renderer->RegisterShader("SimpleShader", "../../Assets/Shaders/vert_normals.glsl", "../../Assets/Shaders/frag_normals.glsl");
	Renderer->RegisterShader("NormalsShader", "../../Assets/Shaders/vert_normals.glsl", "../../Assets/Shaders/frag_normals.glsl");
	Renderer->LoadContent();

	m_pFont->LoadFont("../../Assets/Fonts/consolas.png", "../../Assets/Shaders/vert_font.glsl", "../../Assets/Shaders/frag_font.glsl");
}

void Game::Update(float dt) {
	Input::Instance()->Update(Renderer->Window, dt);
	m_pCamera->Update(Renderer->Window, dt);

	shared_ptr<TransformComponent> transform1 = MakeStrongPtr(m_Actors[0]->GetComponent<TransformComponent>(TransformComponent::g_Name));
	shared_ptr<TransformComponent> transform2 = MakeStrongPtr(m_Actors[1]->GetComponent<TransformComponent>(TransformComponent::g_Name));
	shared_ptr<TransformComponent> transform3 = MakeStrongPtr(m_Actors[2]->GetComponent<TransformComponent>(TransformComponent::g_Name));

	if (transform2->Translation.z >= m_Max) {
		m_Forward1.z = -0.001f;
	}
	else if (transform2->Translation.z <= m_Min) {
		m_Forward1.z = 0.001f;
	}

	if (transform1->Scalar.y >= m_Max/4) {
		m_Forward2.x = -0.001f;
		m_Forward2.y = -0.001f;
		m_Forward2.z = -0.001f;
	}
	else if (transform1->Scalar.y <= 0.2f) {
		m_Forward2.x = 0.001f;
		m_Forward2.y = 0.001f;
		m_Forward2.z = 0.001f;
	}

	if (transform3->Translation.z >= m_Max) {
		m_Forward3.z = -10.0f;
	}
	else if (transform3->Translation.z <= m_Min) {
		m_Forward3.z = 10.0f;
	}

	//transform1->Scale(m_Forward2);
	//transform1->Scalar = vec3(0.1f, 0.1f, 0.1f);
	//transform2->Move(m_Forward1);
	//transform3->Rotate(m_Forward3);
	
}

void Game::Render() {
	Renderer->Begin();

	for (auto actor : m_Actors) {
		actor->Render(Renderer->Shaders(), m_pCamera, vec3(0, 6, 0));
	}

	m_pFont->Print("Hello World", 5, 700, 32);

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

	shared_ptr<MeshComponent> mesh = MakeStrongPtr(actor->GetComponent<MeshComponent>(MeshComponent::g_Name));
	std::cout << "Mesh Component added with texture path: " << mesh->TexturePath << std::endl;
	std::cout << "Mesh Component added with mesh path: " << mesh->MeshPath << std::endl;

	m_Actors.push_back(actor);
}