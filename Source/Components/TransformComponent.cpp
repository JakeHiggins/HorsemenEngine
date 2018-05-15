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

		m_Translation = translation;
		m_Scale = scale;
		m_DegRot = rotation;
		m_RadRot = RotToRad(rotation);

		m_Identity = mat4(1.0f);
		m_Transform = mat4(1.0f);

		m_RebuildTransform = true;
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

void TransformComponent::Move(vec3 delta) {
	m_Translation = m_Translation + delta;
	m_RebuildTransform = true;
}

// Assumes degrees
void TransformComponent::Rotate(vec3 delta) {
	m_DegRot = m_DegRot + delta;
	m_RadRot = RotToRad(m_DegRot);
	m_RebuildTransform = true;
}

void TransformComponent::Scale(vec3 scale) {
	m_Scale = m_Scale + scale;
	m_RebuildTransform = true;
}

mat4 TransformComponent::CalculateTransform()
{
	if (m_RebuildTransform) {
		mat4 rot = glm::toMat4(quat(m_DegRot));
		mat4 trans = glm::translate(m_Identity, m_Translation);
		mat4 scale = glm::scale(m_Identity, m_Scale);

		m_Transform = scale * trans * rot;
		m_RebuildTransform = false;
	}

	return m_Transform;
}

