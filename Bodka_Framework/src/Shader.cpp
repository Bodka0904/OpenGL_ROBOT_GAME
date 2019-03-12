#include "Shader.h"



Shader::Shader(const std::string& filename)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");
	glBindAttribLocation(m_program, 3, "offset");
	
	

	glLinkProgram(m_program);
	glValidateProgram(m_program);

	

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[COLOR_U] = glGetUniformLocation(m_program, "uColor");
	
	
}



Shader::~Shader()
{
	glDeleteProgram(m_program);
	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);

	}
	
}


void Shader::Update(const Transform & transform, const Camera& camera)
{
	
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);

	
	

}

void Shader::UpdateColor(const glm::vec3 color)
{
	glUniform3f(m_uniforms[COLOR_U], color.x, color.y, color.z);
}




void Shader::Bind()
{
	glUseProgram(m_program); 
}

void Shader::UnBind()
{
	glUseProgram(0);
}



std::string Shader::LoadShader(const std::string & filename)
{
	std::ifstream file;
	file.open((filename).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}
	return output;
}

GLuint Shader::CreateShader(const std::string & text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cerr << "Error:Shader creation failed" << std::endl;
	}
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLength[1];

	shaderSourceStrings[0] = text.c_str();    //convert regular string to C-string;
	shaderSourceStringLength[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLength);
	glCompileShader(shader);
	
	return shader;
}


