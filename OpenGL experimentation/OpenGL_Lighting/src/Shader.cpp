#include "shader.h"

ShaderProgram::ShaderProgram(const char* vrtxShaderFile, const char* frgmShaderFile)
{
	int success;
	char errorLog[512];

	std::string src = "";
	std::string temp = "";

	std::fstream fileOpen;

	//Vertex shader
	//Open file

	fileOpen.open(vrtxShaderFile);

	if (!fileOpen.is_open())
	{
		std::cout << "ERR::COULDNT_OPEN_VERTEX_SHADER_FILE" << std::endl;
		fileOpen.close();
	}

	//Read file
	while (std::getline(fileOpen, temp))
	{
		src += temp + "\n";
	}

	fileOpen.close();

	//Create shader from file

	const char* vertexShaderFile = src.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderFile, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cout << "ERR::COULDNT_COMPILE_VERTEX_SHADER" << std::endl;
		std::cout << errorLog << std::endl;
	}

	src = "";
	temp = "";

	//Fragment shader
	//Open file

	fileOpen.open(frgmShaderFile);

	if (!fileOpen.is_open())
	{
		std::cout << "ERR::COULDNT_OPEN_FRAGMENT_SHADER_FILE" << std::endl;
		fileOpen.close();
	}

	//Read file
	while (std::getline(fileOpen, temp))
	{
		src += temp + "\n";
	}

	fileOpen.close();

	//Create shader from file

	const char* fragmentShaderFile = src.c_str();

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderFile, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cout << "ERR::COULDNT_COMPILE_FRAGMENT_SHADER" << std::endl;
		std::cout << errorLog << std::endl;
	}

	src = "";
	temp = "";

	//Program
	//Create program
	unsigned int program;
	program = glCreateProgram();

	//Populate with the shaders
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	//Link program
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, errorLog);
		std::cout << "ERR::COULDNT_LINK_PROGRAM" << std::endl;
		std::cout << errorLog << std::endl;
	}

	this->programId = program;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
	this->Unuse();
}

void ShaderProgram::Use()
{
	glUseProgram(this->programId);
}

void ShaderProgram::Unuse()
{
	glUseProgram(0);
}

void ShaderProgram::ChangeUniform1i(std::string name, int value) const
{
	glUniform1i(glGetUniformLocation(this->programId, name.c_str()), value);
}

void ShaderProgram::ChangeUniform1f(std::string name, float value) const
{
	glUniform1f(glGetUniformLocation(this->programId, name.c_str()), value);
}

void ShaderProgram::ChangeUniform4fv(std::string name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::ChangeUniformMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::ChangeUniformVec3(const std::string& name, const float v0, const float v1, const float v2) const
{
	glUniform3f(glGetUniformLocation(this->programId, name.c_str()), v0, v1, v2);
}

void ShaderProgram::ChangeUniformVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(this->programId, name.c_str()), 1, &value[0]);
}