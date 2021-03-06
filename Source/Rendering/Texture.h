#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
	GLuint m_Image;

public:
	Texture();
	~Texture();

	void LoadTexture(const char* path);
	void Cleanup();

	READONLY_PROPERTY(GLuint, Image);
	GET(Image) { return m_Image; }
	
private:
	void LoadBMP(const char* path);
	void LoadDDS(const char* path);
	void LoadPNG(const char* path);
};

#endif