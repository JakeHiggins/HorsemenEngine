#ifndef SHADERS_H
#define SHADERS_H

class Shaders
{
	public:
		Shaders();
		~Shaders();
		GLuint LoadShaders(const char*, const char*);
};

#endif