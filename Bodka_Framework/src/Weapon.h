#pragma once
#include "Mesh.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>



class FireBalls
{
public:
	FireBalls();
	void SetFireBall(Transform& transform);
	void FireFireBall(Transform& transform);
	void Fire(Transform& transform);
	void DrawFireBall(Mesh& object);
	void CheckIfOutOfGrid(Grid& grid);
	Mesh ball;

private:
	glm::vec3 m_pos;
	glm::vec3 m_direction;
	float m_speed = 0.01f;
	bool fired = false;
	bool readyToFire = true;

	
};


						

