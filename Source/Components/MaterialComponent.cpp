#include "HorsemanStd.h"
#include "MaterialComponent.h"

#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

const char* MaterialComponent::g_Name = "MaterialComponent";

MaterialComponent::MaterialComponent() {
}

MaterialComponent::~MaterialComponent() {
}

bool MaterialComponent::VInit(rapidxml::xml_node<>* pNode)
{
	m_ImagePaths["diffuse"] = nullptr;
	m_ImagePaths["normal"] = nullptr;

	m_pShader = new Shader();

	try {
		if (pNode->first_node("Diffuse") != nullptr) {
			const char* pDiffuse = pNode->first_node("Diffuse")->first_attribute("src")->value();
			m_ImagePaths["diffuse"] = string(strcpy(new char[strlen(pDiffuse) + 1], pDiffuse));
		}

		if (pNode->first_node("Normal") != nullptr) {
			const char* pNormal = pNode->first_node("Normal")->first_attribute("src")->value();
			m_ImagePaths["normal"] = string(strcpy(new char[strlen(pNormal) + 1], pNormal));
		}

		// Custom shader
		if (pNode->first_node("Shader")->first_attribute("src") != nullptr) {
			const char* pShader = pNode->first_node("Shader")->first_attribute("src")->value();
			m_ShaderPath = new char[strlen(pShader) + 1];
			strcpy(m_ShaderPath, pShader);
		}
		// Included shader
		else if (pNode->first_node("Shader")->first_attribute("id") != nullptr) {
			const char* pShader = pNode->first_node("Shader")->first_attribute("id")->value();
			
		}
		// Load standard shader
		// TODO: Add standard shader ID to the component for future loading
		else {
			
		}
	}
	catch (const std::runtime_error& e)
	{
		printf("[MaterialComponent ERROR] Runtime error: %s\n", e.what());
		return false;
	}
	catch (const rapidxml::parse_error& e)
	{
		printf("[MaterialComponent ERROR] Parse error: %s\n", e.what());
		return false;
	}
	catch (const std::exception& e)
	{
		printf("[MaterialComponent ERROR] General error: %s\n", e.what());
		return false;
	}
	catch (int e) {
		printf("[MaterialComponent ERROR] Unknown error occured {ErrorCode: %i}\n", e);
		return false;
	}

	return false;
}

void MaterialComponent::VPostInit()
{
}

void MaterialComponent::VUpdate(float dt)
{
}

void MaterialComponent::VRender(map<string, Shader*> shaders, Camera * cam, vec3 lightPos)
{
}

void MaterialComponent::Cleanup()
{
}
