#include "PlanetarySystem.h"

Planet::Planet(float radius,float angle,glm::vec3 color)	
	:
	planetRadius(radius),
	startAngle(angle),
	color(color)
{
	for (int j = 0; j < n / 2; j++) {
		float theta1 = j * M_PI * 2 / n - M_PI / 2;
		float theta2 = (j + 1) * M_PI * 2 / n - M_PI / 2;
		
		for (int i = 0; i <= n; i++) {
			float theta3 = i * M_PI * 2 / n;
			float ex = planetRadius * cos(theta2) * cos(theta3);
			float ey = planetRadius * sin(theta2);
			float ez = planetRadius * cos(theta2) * sin(theta3);
			
			pos.push_back(glm::vec3(ex, ey, ez));
			ex = planetRadius * cos(theta1) * cos(theta3);
			ey = planetRadius * sin(theta1);
			ez = planetRadius * cos(theta1) * sin(theta3);
			
			pos.push_back(glm::vec3(ex, ey, ez));
		}
		
	}

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);


	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(pos[0]), &pos[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

}

Planet::~Planet()
{
	

}


float Planet::GetRadius()
{
	return planetRadius;
}

void Planet::Move(glm::vec3 centerOfRotation, float radius,float speed, Shader& shader, Camera& camera)
{
	if (!DESTROYED)
	{
		startAngle += 0.0001 * speed;
		transform.GetPos().z = centerOfRotation.z + cos(startAngle) * radius;
		transform.GetPos().x = centerOfRotation.x + sin(startAngle) * radius;
	}
	else if (DESTROYED)
	{
		if (transform.GetScale().x > 0 && transform.GetScale().y > 0 && transform.GetScale().z > 0)
		{
			transform.GetScale().x -= 0.005;
			transform.GetScale().y -= 0.005;
			transform.GetScale().z -= 0.005;
		}

		

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(pos[0]), &pos[0], GL_DYNAMIC_DRAW);
	}
	shader.Update(transform, camera);
	shader.UpdateColor(color);
}

void Planet::Draw()
{

	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_QUADS, 0, pos.size());

	glBindVertexArray(0);
}

void Planet::Destroy()
{
	DESTROYED = true;
}

void Planet::Collision(Mesh & player, Transform & pTransform)
{
	//glm::vec3 absPositionPlayer = glm::vec3(player.GetCenter().x + player.transform.GetPos().x, player.GetCenter().y + player.transform.GetPos().y, player.GetCenter().z + player.transform.GetPos().z);

	//glm::vec3 absPositionSphere = glm::vec3(sphere.GetCenter().x + sphere.transform.GetPos().x, sphere.GetCenter().y + sphere.transform.GetPos().y, sphere.GetCenter().z + sphere.transform.GetPos().z);


	
	
}


