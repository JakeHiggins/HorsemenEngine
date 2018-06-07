#include "HorsemanStd.h"
#include "LightComponent.h"

const char* LightComponent::g_Name = "LightComponent";

LightComponent::LightComponent() {
}

LightComponent::~LightComponent() {
}

bool LightComponent::VInit(rapidxml::xml_node<>* pNode) {
	return false;
}

void LightComponent::VPostInit() {
}

void LightComponent::VUpdate(float dt) {
}

void LightComponent::VRender(Camera * cam, vec3 lightPos) {
}

void LightComponent::Cleanup() {
}
