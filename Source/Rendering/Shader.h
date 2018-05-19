#ifndef SHADERS_H
#define SHADERS_H

class Shader
{
	GLuint m_ProgramID;
	map<string, GLuint> m_Handles;

	public:
		Shader();
		~Shader();
		bool LoadShaders(const char*, const char*);
		void RegisterHandles();
		void Cleanup();
		map<string, GLuint> Handles();

		READONLY_PROPERTY(GLuint, Program);
		GET(Program) { return m_ProgramID; }
};

#endif