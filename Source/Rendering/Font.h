#ifndef FONT_H
#define FONT_H

class Texture;
class Shader;

class Font {
	Texture* m_pTexture;
	Shader* m_pShaders;
	GLuint m_VertexBufferID, m_UVBufferID, m_ShaderID, m_UniformID;
	char* m_CachedText;
	vector<vec2> m_Vertices, m_UVs;

public:
	Font();
	~Font();
	void LoadFont(const char* path, const char* vShader, const char* fShader);
	void Print(const char* text, int x, int y, int size);

	void Cleanup();

private:
	void CacheStatement(const char* text, int x, int y, int size);
};

#endif