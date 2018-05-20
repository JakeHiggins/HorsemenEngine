#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Actors/ActorComponent.h"
#include <glm/gtx/matrix_decompose.hpp>

class TransformComponent : public ActorComponent {

	mat4 m_Transform, m_Identity;
	vec3 m_Translation, m_Scale, m_RadRot, m_DegRot;
	bool m_RebuildTransform;

public:
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	TransformComponent(void) { m_Transform = mat4(); }

	virtual bool VInit(rapidxml::xml_node<>* pNode);
	virtual void VPostInit();
	virtual void VUpdate(float dt);
	virtual void VRender(map<string, GLuint> handles, Camera* cam, vec3 lightPos);

	void Move(vec3 position);
	void Rotate(vec3 euler);
	void Scale(vec3 scale);

#pragma region Properties
	READONLY_PROPERTY(mat4, Transform);
	GET(Transform) { return CalculateTransform(); }

	PROPERTY(vec3, Translation);
	GET(Translation) { return m_Translation; }
	SET(Translation) { m_Translation = value; m_RebuildTransform = true; }

	PROPERTY(vec3, Scalar);
	GET(Scalar) { return m_Scale; }
	SET(Scalar) { m_Scale = value; m_RebuildTransform = true; }

	// Default Rotation returns Degrees
	PROPERTY(vec3, Rotation);
	GET(Rotation) { return m_DegRot; }
	SET(Rotation) { m_DegRot = value; m_RadRot = RotToRad(value); m_RebuildTransform = true; }

	PROPERTY(vec3, RotationRads);
	GET(RotationRads) { return m_RadRot; }
	SET(RotationRads) { m_RadRot = value; m_DegRot = RotToDeg(value); m_RebuildTransform = true; }
	#pragma endregion

	// Creator for ActorFactory
	// TODO: Put all these in a single place
	static ActorComponent* __stdcall Create() { return new TransformComponent(); }

private:
	vec3 RotToRad(vec3 rot) { return vec3(rot.x * DEG2RAD, rot.y * DEG2RAD, rot.z * DEG2RAD); }
	vec3 RotToDeg(vec3 rot) { return vec3(rot.x * RAD2DEG, rot.y * RAD2DEG, rot.z * RAD2DEG); }

	mat4 CalculateTransform();
};

#endif