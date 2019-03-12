#pragma once

#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include "Transform.h"
#include "Camera.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>



class Shader
{
public:
	Shader(const std::string& filename);

	void Update(const Transform& transform,const Camera& camera);
	void UpdateColor(const glm::vec3 color);
	void Bind();
	void UnBind();
	
	
	
	static std::string LoadShader(const std::string& filename);
	static GLuint CreateShader(const std::string& text, GLenum shaderType);
		
	virtual ~Shader();

private:
	static const unsigned int NUM_SHADER = 2;

	enum
	{
		TRANSFORM_U,

		COLOR_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADER];
	GLuint m_uniforms[NUM_UNIFORMS];
	

	
};

