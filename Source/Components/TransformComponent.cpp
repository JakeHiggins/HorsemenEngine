#include "HorsemanStd.h"
#include "TransformComponent.h"

const char* TransformComponent::g_Name = "TransformComponent";

bool TransformComponent::VInit(rapidxml::xml_node<>* pNode)
{
	try {
		rapidxml::xml_node<>* pTransNode = pNode->first_node("Translation");
		rapidxml::xml_node<>* pRotNode = pNode->first_node("Rotation");
		rapidxml::xml_node<>* pScaleNode = pNode->first_node("Scale");

		vec3 translation = vec3(
			std::atof(pTransNode->first_attribute("x")->value()),
			std::atof(pTransNode->first_attribute("y")->value()),
			std::atof(pTransNode->first_attribute("z")->value())
		);

		vec3 rotation = vec3(
			std::atof(pRotNode->first_attribute("yaw")->value()),
			std::atof(pRotNode->first_attribute("pitch")->value()),
			std::atof(pRotNode->first_attribute("roll")->value())
		);

		vec3 scale = vec3(
			std::atof(pScaleNode->first_attribute("x")->value()),
			std::atof(pScaleNode->first_attribute("y")->value()),
			std::atof(pScaleNode->first_attribute("z")->value())
		);

		m_Transform = glm::translate(m_Transform, translation);
		glm::decompose(m_Transform, m_Scale, m_Rotation, m_Origin, m_Skew, m_Perspective);
		m_Transform = glm::scale(m_Transform, scale);
		glm::decompose(m_Transform, m_Scale, m_Rotation, m_Translation, m_Skew, m_Perspective);
	}
	catch (const std::runtime_error& e)
	{
		printf("[TransformComponent ERROR] Runtime error: %s\n", e.what());
		return false;
	}
	catch (const rapidxml::parse_error& e)
	{
		printf("[TransformComponent ERROR] Parse error: %s\n", e.what());
		return false;
	}
	catch (const std::exception& e)
	{
		printf("[TransformComponent ERROR] General error: %s\n", e.what());
		return false;
	}
	catch (int e) {
		printf("[TransformComponent ERROR] Unknown error occured {ErrorCode: %i}\n", e);
		return false;
	}
	// TODO: Implement rotation

	return true;
}

void TransformComponent::VPostInit()
{
}

void TransformComponent::VUpdate(float dt)
{
}

void TransformComponent::VRender(map<string, GLuint> handles, Camera * cam, vec3 lightPos)
{
}

void TransformComponent::Move(vec3 position) {
	m_Transform = glm::translate(m_Transform, position);
}

