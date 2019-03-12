#pragma once
#include "SDL.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>



class Planet
{
public:
	Planet(float radius, float angle,glm::vec3 color);
	~Planet();

	float GetRadius();
	void Move(glm::vec3 centerOfRotation, float radius, float speed, Shader& shader,Camera& camera);
	void Draw();
	void Destroy();

	void Collision(Mesh& player, Transform& pTransform);
	
private:
	float planetRadius;
	float n = planetRadius * 5;
	float startAngle;
	
	glm::vec3 color;
	std::vector < glm::vec3 > pos;

	bool DESTROYED = false;

	enum
	{
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

public:
	Transform transform;
};




