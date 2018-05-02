#ifndef SHADERS_H
#define SHADERS_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class Shaders
{
	public:
		Shaders();
		~Shaders();
		GLuint LoadShaders(const char*, const char*);
};

#endif