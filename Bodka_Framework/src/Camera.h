#pragma once
#include <iostream>
#include "Transform.h"
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "GL\glew.h"


class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 0.5, 0);
		
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, cameraCenter , m_up);
	}

	glm::vec3& GetPos() { return m_position; }

	
	
	void CameraFollow(Transform& transform);
	void CameraUpDown(Transform& transform,float number);
	glm::vec3 GetCenter(Transform& transform) { return transform.GetPos(); }
	
	
	

private:
	
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::vec3 cameraCenter;
	float lastValue = 0;
	float cameraDistance = 2;
	
	
	

	
	
	
	
};
