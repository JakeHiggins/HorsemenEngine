#ifndef FONT_H
#define FONT_H

class Texture;
class Shader;

class Font {
	Texture* m_pTexture;
	Shader* m_pShader;
	GLuint m_VertexBufferID, m_UVBufferID, m_UniformID;
	char* m_CachedText;
	vector<vec2> m_Vertices, m_UVs;

public:
	Font();
	~Font();
	void LoadFont(const char* path, const char* vShader, const char* fShader);
	bool LoadFont(const char* name);
	void Print(const char* text, int x, int y, int size);
	void Print(string text, int x, int y, int size);
	void Print(double text, int x, int y, int size);
	void Print(int text, int x, int y, int size);
	void Print(float text, int x, int y, int size);

	void Cleanup();

private:
	void CacheStatement(const char* text, int x, int y, int size);
};

#endif