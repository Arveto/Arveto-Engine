
#pragma once

#include <string>

class Shader{
	private:
		void checkCompileErrors(unsigned int shader, std::string type);

	public:
		unsigned int ID;

		Shader(char const * vertexPath, char const * fragmentPath);

		void use();
		void desactive();

		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
};