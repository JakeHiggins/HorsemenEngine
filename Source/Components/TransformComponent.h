#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Actors/ActorComponent.h"
#include <glm/gtx/matrix_decompose.hpp>

class TransformComponent : public ActorComponent {

	mat4 m_Transform;
	vec3 m_Translation;
	vec3 m_Scale;
	quat m_Rotation;
	vec3 m_Skew;
	vec4 m_Perspective;

public:
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	TransformComponent(void) { m_Transform = mat4(); }

	virtual bool VInit(rapidxml::xml_node<>* pNode);
	virtual void VPostInit();
	virtual void VUpdate(float dt);

	#pragma region Properties
	READONLY_PROPERTY(mat4, Transform);
	GET(Transform) { return m_Transform; };

	READONLY_PROPERTY(vec3, Translation);
	GET(Translation) {
		glm::decompose(m_Transform, m_Scale, m_Rotation, m_Translation, m_Skew, m_Perspective);
		return m_Translation; 
	};

	READONLY_PROPERTY(vec3, Scale);
	GET(Scale) {
		glm::decompose(m_Transform, m_Scale, m_Rotation, m_Translation, m_Skew, m_Perspective);
		return m_Scale;
	};

	READONLY_PROPERTY(quat, Rotation);
	GET(Rotation) {
		glm::decompose(m_Transform, m_Scale, m_Rotation, m_Translation, m_Skew, m_Perspective);
		return m_Rotation;
	};

	READONLY_PROPERTY(vec3, Skew);
	GET(Skew) {
		glm::decompose(m_Transform, m_Scale, m_Rotation, m_Translation, m_Skew, m_Perspective);
		return m_Skew;
	};

	READONLY_PROPERTY(vec3, Perspective);
	GET(Perspective) {
		glm::decompose(m_Transform, m_Scale, m_Rotation, m_Translation, m_Skew, m_Perspective);
		return m_Perspective;
	};
	#pragma endregion

	// Creator for ActorFactory
	// TODO: Put all these in a single place
	static ActorComponent* __stdcall Create() { return new TransformComponent(); }
};

#endif