#pragma once
#include "SDL.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"
#include <string>
#include <GL/glew.h>
#include <iostream>
#include <math.h> 

class Terrain
{
public:
	Terrain(std::string filename,float size,float h,glm::vec3 color);
	~Terrain();


	void Draw(Shader& shader,Camera& camera);
	float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
	void Collision(Transform& player);
	float GetSize() { return heights.size() * m_size; }
	

	

private:
	std::vector < std::vector<float> > heights;
	std::vector<glm::vec3> pos;
	std::vector <unsigned int> indices;

	
	glm::vec3 color;
	
	
private:	
	enum
	{
		POSITION_VB,

		TEXCOORD_VB,

		INDEX_VB,

		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

	float m_size;
	float m_height;
public:
	Transform transform;
	

};




