#include "Camera.h"







void Camera::CameraFollow(Transform & transform)
{
	
	float old = lastValue;
	lastValue = transform.GetRot().y;
	float newValue = lastValue - old;
	
	m_position.x = -sin(transform.GetRot().y) * cameraDistance + transform.GetPos().x;
	m_position.z = -cos(transform.GetRot().y) * cameraDistance + transform.GetPos().z;
	m_position.y = transform.GetPos().y + 0.5;
	

	
	cameraCenter = GetCenter(transform);

	
}

void Camera::CameraUpDown(Transform & transform,float number)
{
	m_position.y += number ;
}


	

	
