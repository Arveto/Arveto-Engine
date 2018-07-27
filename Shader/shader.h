#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
private:
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
		//TODO Automatically calculate matrices based on camera data?

	void checkCompileErrors(unsigned int shader, std::string type);

public:
	unsigned int ID;

	Shader(std::string vertexPath, std::string fragmentPath);

	void use();
	void disable();

	void setModelMatrix(glm::mat4 newModelMatrix);
	void setViewMatrix(glm::mat4 newViewMatrix);
	void setProjectionMatrix(glm::mat4 newProjectionMatrix);
		//TODO Automatically bind using camera data?

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};
