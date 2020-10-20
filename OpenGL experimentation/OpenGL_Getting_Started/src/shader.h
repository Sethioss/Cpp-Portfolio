#pragma once
#include "libs.h"

class ShaderProgram
{
public:
	unsigned int programId;

	ShaderProgram(const char* vrtxShaderFile, const char* frgmShaderFile);
	~ShaderProgram();
	void Use();
	void Unuse();
	void ChangeUniform1i(std::string name, int value) const;
	void ChangeUniform1f(std::string name, float value) const;
	void ChangeUniform4fv(std::string name, glm::mat4 value) const;
	void ChangeUniformMat4(const std::string& name, const glm::mat4& mat) const;
};