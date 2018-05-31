#include "HorsemanStd.h"
#include "MaterialComponent.h"

#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

const char* MaterialComponent::g_Name = "MaterialComponent";

MaterialComponent::MaterialComponent() {
}

MaterialComponent::~MaterialComponent() {
	SAFE_DELETE(m_pShader);
	m_ImagePaths.clear();
	m_Textures.clear();
}

bool MaterialComponent::VInit(rapidxml::xml_node<>* pNode)
{
	m_ImagePaths["diffuse"] = config.EngineAssets + string("/Textures/missing_d.png");
	m_ImagePaths["normal"] = config.EngineAssets + string("/Textures/missing_n.png");

	m_Textures["diffuse"] = new Texture();
	m_Textures["normal"] = new Texture();

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
		if (pNode->first_node("Shader") != nullptr) {
			if (pNode->first_node("Shader")->first_attribute("vshader") != nullptr && pNode->first_node("Shader")->first_attribute("fshader")) {
				const char* pVShader = pNode->first_node("Shader")->first_attribute("vshader")->value();
				const char* pFShader = pNode->first_node("Shader")->first_attribute("fshader")->value();
				m_VShaderPath = new char[strlen(pVShader) + 1];
				strcpy(m_VShaderPath, pVShader);
				m_FShaderPath = new char[strlen(pFShader) + 1];
				strcpy(m_FShaderPath, pFShader);
			}
			// Included shader
			else if (pNode->first_node("Shader")->first_attribute("id") != nullptr) {
				const char* pShader = pNode->first_node("Shader")->first_attribute("id")->value();
				if (string("bump_diffuse").compare(pShader) == 0) {
					m_VShaderPath = new char[strlen(config.EngineAssets.c_str()) + 34];
					strcpy(m_VShaderPath, config.EngineAssets.c_str());
					strcat(m_VShaderPath, "/Shaders/vert_bump_diffuse.glsl");

					m_FShaderPath = new char[strlen(config.EngineAssets.c_str()) + 34];
					strcpy(m_FShaderPath, config.EngineAssets.c_str());
					strcat(m_FShaderPath, "/Shaders/frag_bump_diffuse.glsl");
				}
				else if (string("transparent").compare(pShader) == 0) {
					m_VShaderPath = new char[strlen(config.EngineAssets.c_str()) + 33];
					strcpy(m_VShaderPath, config.EngineAssets.c_str());
					strcat(m_VShaderPath, "/Shaders/vert_transparent.glsl");

					m_FShaderPath = new char[strlen(config.EngineAssets.c_str()) + 33];
					strcpy(m_FShaderPath, config.EngineAssets.c_str());
					strcat(m_FShaderPath, "/Shaders/frag_transparent.glsl");
				}
				else {
					LoadDefaultShader();
				}
			}
			// Load standard shader
			else {
				LoadDefaultShader();
			}
		}
		else {
			LoadDefaultShader();
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

	return true;
}

void MaterialComponent::VPostInit() {
	bool result = m_pShader->LoadShaders(m_VShaderPath, m_FShaderPath);
	if (result) {
		m_pShader->RegisterHandles();
	}

	m_Textures["diffuse"]->LoadTexture(m_ImagePaths["diffuse"].c_str());
	m_Textures["normal"]->LoadTexture(m_ImagePaths["normal"].c_str());
}

void MaterialComponent::VUpdate(float dt)
{
}

void MaterialComponent::VRender(Camera * cam, vec3 lightPos) {

}

void MaterialComponent::Cleanup() {
	for (auto texture : m_Textures) {
		texture.second->Cleanup();
	}

	m_pShader->Cleanup();
}

void MaterialComponent::BindTextures() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Textures["diffuse"]->Image);
	glUniform1i(m_pShader->Handles()["DiffuseID"], 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_Textures["normal"]->Image);
	glUniform1i(m_pShader->Handles()["NormalID"], 1);
}

void MaterialComponent::LoadDefaultShader() {
	m_VShaderPath = new char[strlen(config.EngineAssets.c_str()) + 29];
	strcpy(m_VShaderPath, config.EngineAssets.c_str());
	strcat(m_VShaderPath, "/Shaders/vert_diffuse.glsl");

	m_FShaderPath = new char[strlen(config.EngineAssets.c_str()) + 29];
	strcpy(m_FShaderPath, config.EngineAssets.c_str());
	strcat(m_FShaderPath, "/Shaders/frag_diffuse.glsl");
}
