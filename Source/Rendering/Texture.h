#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	Texture();
	~Texture();

	void LoadBMP(const char* path);
	void LoadDDS(const char* path);
	void Cleanup();

	READONLY_PROPERTY(GLuint, Image);
	GET(Image) { return m_Image; }

private:
	GLuint m_Image;
};

#endif