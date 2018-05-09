#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
	GLuint m_Image;

public:
	Texture();
	~Texture();

	void LoadBMP(const char* path);
	void LoadDDS(const char* path);
	void Cleanup();

	READONLY_PROPERTY(GLuint, Image);
	GET(Image) { return m_Image; }
	
};

#endif