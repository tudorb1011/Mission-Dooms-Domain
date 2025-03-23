#pragma once

#include <glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <../glm/glm.hpp>  // Include glm for matrix types

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void use();
	int getId();

	// Add the method to set a mat4 uniform
	void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
	unsigned int id;
};
