#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <stdio.h>

#include "../Utils/properties.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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