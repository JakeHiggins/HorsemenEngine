#include "HorsemanStd.h"
#include "MeshComponent.h"

#include "Rendering/Texture.h"
#include "Camera.h"
#include "Input/Input.h"
#include "Utils/loaders.h"

const char* MeshComponent::g_Name = "MeshComponent";

MeshComponent::MeshComponent(vec3 position) {
	m_Transform = mat4();
	m_Position = position;
	m_Rotation = vec3(0, 0, 0);
	m_Scale = vec3(1, 1, 1);

	m_Transform = translate(m_Transform, position);
}

MeshComponent::~MeshComponent() {
}

bool MeshComponent::VInit(rapidxml::xml_node<>* pNode)
{
	return true;
}

void MeshComponent::VPostInit()
{
}

void MeshComponent::VUpdate(float dt)
{
}

void MeshComponent::Init() {
	m_pTexture = new Texture();
}

void MeshComponent::LoadContent(const char* model, const char* texture) {
	m_pTexture->LoadDDS(texture);
	bool res = LoadObj(model, m_Vertices, m_UVs, m_Normals);
	if(!res) { printf("ModelLoadError [%s]: Model could not be loaded.\n", model); return; }

	// Create VAO
	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(vec3), &m_Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_UVs.size() * sizeof(vec2), &m_UVs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_NormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_Normals.size() * sizeof(vec3), &m_Normals[0], GL_STATIC_DRAW);
}

void MeshComponent::Update(float dt) {
	
}

void MeshComponent::Render(map<string, GLuint> handles, Camera* cam, vec3 lightPos) {
	// Use shader
	glUseProgram(handles["ProgramID"]);

	// Update and send MVP
	mat4 mvp = cam->Projection * cam->View * m_Transform;
	mat4 view = cam->View;
	glUniformMatrix4fv(handles["MatrixID"], 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(handles["ModelMatID"], 1, GL_FALSE, &m_Transform[0][0]);
	glUniformMatrix4fv(handles["ViewMatID"], 1, GL_FALSE, &view[0][0]);

	// Bind light
	glUniform3f(handles["LightID"], lightPos.x, lightPos.y, lightPos.z);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pTexture->Image);
	glUniform1i(handles["TextureID"], 0);

	// Bind vertex array
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Bind color array
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	// Bind the normal array
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_Vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void MeshComponent::Cleanup() {
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_UVBuffer);
	glDeleteVertexArrays(1, &m_VertexArrayID);

	m_pTexture->Cleanup();
	SAFE_DELETE(m_pTexture);
}

void MeshComponent::SetPosition(vec3 pos)
{
	m_Position = pos;
}
