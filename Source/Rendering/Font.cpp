#include "HorsemanStd.h"
#include "Font.h"

#include "Texture.h"
#include "Shader.h"

Font::Font() {
	m_pTexture = new Texture();
	m_pShader = new Shader();
}

Font::~Font() {
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pShader);
}

void Font::LoadFont(const char * path, const char* vShader, const char* fShader) {
	m_pTexture->LoadTexture(path);

	glGenBuffers(1, &m_VertexBufferID);
	glGenBuffers(1, &m_UVBufferID);

	bool result = m_pShader->LoadShaders(vShader, fShader);

	m_UniformID = glGetUniformLocation(m_pShader->Program, "textureSampler");
}

void Font::Print(const char * text, int x, int y, int size) {
	if (text != m_CachedText)
		CacheStatement(text, x, y, size);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(vec2), &m_Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_UVs.size() * sizeof(vec2), &m_UVs[0], GL_STATIC_DRAW);

	glUseProgram(m_pShader->Program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pTexture->Image);
	glUniform1i(m_UniformID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
	glDisable(GL_BLEND);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Font::Print(string text, int x, int y, int size) { Print(text.c_str(), x, y, size); }

void Font::Print(double text, int x, int y, int size) { Print(toCString(text), x, y, size); }

void Font::Print(int text, int x, int y, int size) { Print(toCString(text), x, y, size); }

void Font::Print(float text, int x, int y, int size) { Print(toCString(text), x, y, size); }

void Font::Cleanup() {
	glDeleteBuffers(1, &m_VertexBufferID);
	glDeleteBuffers(1, &m_UVBufferID);

	m_pTexture->Cleanup();
	m_pShader->Cleanup();
}

void Font::CacheStatement(const char * text, int x, int y, int size) {
	m_CachedText = new char[strlen(text) + 1];
	strcpy(m_CachedText, text);
	m_Vertices.clear();
	m_UVs.clear();

	unsigned int length = strlen(text);

	for (unsigned int i = 0; i < length; i++) {
		vec2 vTopLeft = vec2(x + i * size, y + size);
		vec2 vTopRight = vec2(x + i * size + size, y + size);
		vec2 vBotRight = vec2(x + i * size + size, y);
		vec2 vBotLeft = vec2(x + i * size, y);

		m_Vertices.push_back(vTopLeft);
		m_Vertices.push_back(vBotLeft);
		m_Vertices.push_back(vTopRight);

		m_Vertices.push_back(vBotRight);
		m_Vertices.push_back(vTopRight);
		m_Vertices.push_back(vBotLeft);

		char character = text[i];
		vec2 uv = vec2((character % 16) / 16.0f, (character / 16) / 16.0f);

		vec2 uTopLeft = vec2(uv.x, uv.y);
		vec2 uTopRight = vec2(uv.x + 1.0f / 16.0f, uv.y);
		vec2 uBotRight = vec2(uv.x + 1.0f / 16.0f, uv.y + 1.0f / 16.0f);
		vec2 uBotLeft = vec2(uv.x, uv.y + 1.0f / 16.0f);

		m_UVs.push_back(uTopLeft);
		m_UVs.push_back(uBotLeft);
		m_UVs.push_back(uTopRight);

		m_UVs.push_back(uBotRight);
		m_UVs.push_back(uTopRight);
		m_UVs.push_back(uBotLeft);
	}

}
