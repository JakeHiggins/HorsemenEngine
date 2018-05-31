#include "HorsemanStd.h"
#include "Shader.h"

#include <fstream>
#include <sstream>

Shader::Shader() {
}


Shader::~Shader() {
}

// Included shader types
#define HSHADER_STANDARD_ID 0
#define HSHADER_STANDARD_BUMP_ID 1
#define HSHADER_PATH "Assets/Shaders/"
#define HSHADER_STANDARD_EXT "standard"
#define HSHADER_STANDARD_BUMP_EXT "standard_bump"


bool Shader::LoadShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader from file
	string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);

	if (vertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
	else {
		printf("Failed to open vertex shader %s", vertexShaderPath);
		getchar();
		return false;
	}

	// Read fragment shader
	string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentShaderPath, std::ios::in);

	if (fragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}
	else {
		printf("Failed to open fragment shader %s", fragmentShaderPath);
		getchar();
		return false;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile vertex shader
	printf("Compiling vertex shader : %s\n", vertexShaderPath);
	const char* pVertexSource = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &pVertexSource, NULL);
	glCompileShader(vertexShaderID);

	// Check vertex shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
		return false;
	}

	// Compile fragment shader
	printf("Compiling fragment shader : %s\n", fragmentShaderPath);
	const char* pFragmentShader = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &pFragmentShader, NULL);
	glCompileShader(fragmentShaderID);

	// Check fragment shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
		return false;
	}

	// Link the program
	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
		return false;
	}

	// Clean up shaders
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	m_ProgramID = programID;

	return true;
}

void Shader::RegisterHandles() {
	m_Handles["MatrixID"] = glGetUniformLocation(m_ProgramID, "MVP");
	m_Handles["ModelMatID"] = glGetUniformLocation(m_ProgramID, "M");
	m_Handles["ViewMatID"] = glGetUniformLocation(m_ProgramID, "V");
	m_Handles["DiffuseID"] = glGetUniformLocation(m_ProgramID, "DiffuseTextureSampler");
	m_Handles["NormalID"] = glGetUniformLocation(m_ProgramID, "NormalTextureSampler");
	m_Handles["MV3x3ID"] = glGetUniformLocation(m_ProgramID, "MV3x3");
	m_Handles["LightID"] = glGetUniformLocation(m_ProgramID, "LightPosition_worldspace");
}

void Shader::Cleanup() {
	glDeleteProgram(m_ProgramID);
}

map<string, GLuint> Shader::Handles()
{
	return m_Handles;
}