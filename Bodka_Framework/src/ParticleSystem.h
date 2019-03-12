#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"
#include <cstdlib>
#include <random>
#include <math.h>
#include <vector>

enum PARTICLE_TYPE
{
	JET,

	CORE,

	NUM_TYPES
};

class ParticleSystem
{
public:
	ParticleSystem(int numParticles, float Gravity, float Radius, float size,glm::vec3 color, PARTICLE_TYPE TYPE);
	~ParticleSystem();

	void Update(float dt,Shader& shader);
	void Explode() { EXPLODE = true; }
	void Reset();
	void Draw();

	float RandomFloat();


private:
	int numParticles;
	float size;
	float speed = 50; //lower number is faster


	std::vector<glm::vec3> offsets;
	std::vector<glm::vec3> velocity;

	std::vector<float> timeAlive;
	std::vector<float> lifeSpan;

	float Gravity;
	float Radius;
	PARTICLE_TYPE P_TYPE;

private:
	bool RESET = false;
	bool EXPLODE = false;

	float count = 0;
	glm::vec3 vertices[8] = {
		glm::vec3(-size, -size,  size),
		glm::vec3(size, -size,  size),
		glm::vec3(size,  size,  size),
		glm::vec3(-size,  size,  size),

		glm::vec3(-size, -size, -size),
		glm::vec3(size, -size, -size),
		glm::vec3(size,  size, -size),
		glm::vec3(-size,  size, -size)

	};
	glm::vec3 color;
	
	unsigned int indices[36] = { 
		0, 1, 2,
		2, 3, 0,
		1, 5, 6,
		6, 2, 1,
		7, 6, 5,
		5, 4, 7,
		4, 0, 3,
		3, 7, 4,
		4, 5, 1,
		1, 0, 4,
		3, 2, 6,
		6, 7, 3 };
	
private:
	enum
	{
		POSITION_VB,

		COLOR_VB,

		OFFSET_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
public:
	Transform transform;
	
	
};



