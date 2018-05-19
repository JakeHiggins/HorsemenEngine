#include "HorsemanStd.h"
#include "MeshComponent.h"

#include "Camera.h"
#include "TransformComponent.h"
#include "Input/Input.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Utils/loaders.h"

const char* MeshComponent::g_Name = "MeshComponent";

MeshComponent::MeshComponent() {
	m_RenderNormal = false;
}

MeshComponent::~MeshComponent() {
}

bool MeshComponent::VInit(rapidxml::xml_node<>* pNode) {
	m_pTexture = new Texture();
	m_pNormal = new Texture();

	try {
		const char* pTexture = pNode->first_node("Texture")->first_attribute("src")->value();
		m_TexturePath = new char[strlen(pTexture) + 1];
		strcpy(m_TexturePath, pTexture);

		m_RenderNormal = pNode->first_node("Normal") != nullptr;
		if (m_RenderNormal) {
			const char* pNormal = pNode->first_node("Normal")->first_attribute("src")->value();
			m_NormalPath = new char[strlen(pNormal) + 1];
			strcpy(m_NormalPath, pNormal);
		}

		const char* pMesh = pNode->first_node("Mesh")->first_attribute("src")->value();
		m_MeshPath = new char[strlen(pMesh) + 1];
		strcpy(m_MeshPath, pMesh);

		const char* pShader = pNode->first_node("Shader")->first_attribute("id")->value();
		m_Shader = new char[strlen(pShader) + 1];
		strcpy(m_Shader, pShader);
	}
	catch (const std::runtime_error& e)
	{
		printf("[MeshComponent ERROR] Runtime error: %s\n", e.what());
		return false;
	}
	catch (const rapidxml::parse_error& e)
	{
		printf("[MeshComponent ERROR] Parse error: %s\n", e.what());
		return false;
	}
	catch (const std::exception& e)
	{
		printf("[MeshComponent ERROR] General error: %s\n", e.what());
		return false;
	}
	catch (int e) {
		printf("[MeshComponent ERROR] Unknown error occured {ErrorCode: %i}\n", e);
		return false;
	}

	return true;
}

void MeshComponent::VPostInit() {
	m_pTexture->LoadTexture(m_TexturePath);
	if (m_RenderNormal) {
		m_pNormal->LoadTexture(m_NormalPath);
	}

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;
	bool res = LoadObj(m_MeshPath, vertices, uvs, normals);

	vector<vec3> tangents;
	vector<vec3> bitangents;
	ComputeTangedBasis(vertices, uvs, normals, tangents, bitangents);

	// Index model
	IndexVBO(
		vertices, uvs, normals, tangents, bitangents,
		m_Indices, m_Vertices, m_UVs, m_Normals, m_Tangents, m_Bitangents);

	if (!res) { printf("ModelLoadError [%s]: Model could not be loaded.\n", m_MeshPath); return; }

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

	glGenBuffers(1, &m_TangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_TangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_Tangents.size() * sizeof(vec3), &m_Tangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_BitangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_BitangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_Bitangents.size() * sizeof(vec3), &m_Bitangents[0], GL_STATIC_DRAW);

	// Create VBO
	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned short), &m_Indices[0], GL_STATIC_DRAW);
}

void MeshComponent::VUpdate(float dt) {
}

void MeshComponent::VRender(map<string, Shader*> shaders, Camera* cam, vec3 lightPos) {
	mat4 transform = GetTransform();

	GLuint program = shaders[m_Shader]->Program;
	map<string, GLuint> handles = shaders[m_Shader]->Handles();

	// Use shader
	glUseProgram(program);

	// Update and send MVP
	mat4 mvp = cam->Projection * cam->View * transform;
	mat4 view = cam->View;
	mat3 modelView = mat3(view * transform);
	glUniformMatrix4fv(handles["MatrixID"], 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(handles["ModelMatID"], 1, GL_FALSE, &transform[0][0]);
	glUniformMatrix4fv(handles["ViewMatID"], 1, GL_FALSE, &view[0][0]);
	glUniformMatrix3fv(handles["MV3x3ID"], 1, GL_FALSE, &modelView[0][0]);

	// Bind light
	glUniform3f(handles["LightID"], lightPos.x, lightPos.y, lightPos.z);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pTexture->Image);
	glUniform1i(handles["TextureID"], 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pNormal->Image);
	glUniform1i(handles["NormalID"], 1);

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

	// Bind the Tangent array
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, m_TangentBuffer);
	glVertexAttribPointer(
		3,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	// Bind the Bitangent array
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, m_BitangentBuffer);
	glVertexAttribPointer(
		4,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	//glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_Vertices.size());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

	// Enable blending
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawElements(
		GL_TRIANGLES,
		m_Indices.size(),
		GL_UNSIGNED_SHORT,
		(void*)0
	);

	//glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

void MeshComponent::Cleanup() {
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_UVBuffer);
	glDeleteBuffers(1, &m_NormalBuffer);
	glDeleteBuffers(1, &m_IndexBuffer);
	glDeleteBuffers(1, &m_TangentBuffer);
	glDeleteBuffers(1, &m_BitangentBuffer);

	glDeleteVertexArrays(1, &m_VertexArrayID);

	m_pTexture->Cleanup();
	m_pNormal->Cleanup();

	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pNormal);
}

mat4 MeshComponent::GetTransform() {
	shared_ptr<TransformComponent> pTransform = MakeStrongPtr(m_pOwner->GetComponent<TransformComponent>(TransformComponent::g_Name));
	return pTransform->Transform;
}
