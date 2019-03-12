#include "ParticleSystem.h"



ParticleSystem::ParticleSystem(int numParticles, float Gravity,float Radius, float size, glm::vec3 color, PARTICLE_TYPE TYPE)
	:
	numParticles(numParticles),
	Gravity(Gravity),
	Radius(Radius),
	size(size),
	color(color),
	P_TYPE(TYPE)
{
	offsets.resize(numParticles);
	velocity.resize(numParticles);
	timeAlive.resize(numParticles);
	lifeSpan.resize(numParticles);
	 
	if (P_TYPE == JET)
	{
		for (int i = 0; i < numParticles; ++i)
		{
			if (i >= numParticles / 2)
			{
				offsets[i] = glm::vec3(-0.25, 0, 0);
			}
			else
			{
				offsets[i] = glm::vec3(0.3, 0, 0);
			}
			velocity[i] = glm::vec3(
				(0.5 * RandomFloat() - 0.25f) / speed,
				(Gravity * 0.5 * RandomFloat() - 0.25f) / speed,
				(0.5 * RandomFloat() - 0.25f) / speed);



			if (velocity[i].y >= 0.25)
			{
				velocity[i].y = 0;
			}

			timeAlive[i] = 0;
			lifeSpan[i] = RandomFloat() + 1.5f;

		}
	}
	else if (P_TYPE == CORE)
	{
		for (int i = 0; i < numParticles; ++i)
		{
			offsets[i] = glm::vec3(0, 0, 0);
			velocity[i] = glm::vec3(
				(0.5 * RandomFloat() - 0.25f) / speed,
				(0.5 * RandomFloat() - 0.25f) / speed,
				(0.5 * RandomFloat() - 0.25f) / speed);
		}
	}
	/////////////////////////////////////////
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);


	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOR_VB]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(color), &color, GL_STATIC_DRAW);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[OFFSET_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * numParticles, 0, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribDivisor(3, 1);

		
	glBindVertexArray(0);
}


ParticleSystem::~ParticleSystem()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}



void ParticleSystem::Update(float dt,Shader& shader)
{
	shader.UpdateColor(color);

	if (P_TYPE == JET)
	{
		for (int i = 0; i < numParticles; ++i)
		{
			if (!RESET)
			{
				offsets[i].x += velocity[i].x;
				offsets[i].y += velocity[i].y;
				offsets[i].z += velocity[i].z;
			}
			else if (RESET)
			{
				if (i >= numParticles / 2)
				{
					offsets[i] = glm::vec3(0.3, 0, 0);
				}
				else
				{
					offsets[i] = glm::vec3(-0.25, 0, 0);
				}
			}
			timeAlive[i] += dt;
			if (timeAlive[i] >= lifeSpan[i])
			{

				timeAlive[i] = 0;

				if (i >= numParticles / 2)
				{
					offsets[i] = glm::vec3(0.3, 0, 0);
				}
				else
				{
					offsets[i] = glm::vec3(-0.25, 0, 0);
				}
			}

		}
	}
	else if (P_TYPE == CORE)
	{
		if (EXPLODE)
		{
			count += dt;
		}
		else
		{
			count = 0;
		}
		for (int i = 0; i < numParticles; ++i)
		{
			if (!EXPLODE)
			{
				offsets[i].x += velocity[i].x;
				offsets[i].y += velocity[i].y;
				offsets[i].z += velocity[i].z;
				if (pow(offsets[i].x, 2) + pow(offsets[i].y, 2) + pow(offsets[i].z, 2) >= pow(Radius, 2))
				{

					offsets[i].x = 0;
					offsets[i].y = 0;
					offsets[i].z = 0;
				}
			}
			else if (EXPLODE)
			{
				
				if (count < 0.8)
				{
					offsets[i].x -= velocity[i].x * 2;
					offsets[i].y -= velocity[i].y * 2;
					offsets[i].z -= velocity[i].z * 2;
				}
				else
				{	
					if(abs(velocity[i].x * 50) - count / 1000 > 0 && abs(velocity[i].z * 20) - count / 1000 > 0 )
					{
						offsets[i].x += (velocity[i].x * 50) - count / 1000;
						offsets[i].z += (velocity[i].z * 50) - count / 1000;
					}
				}
			}
			
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[OFFSET_VB]);
	glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(glm::vec3), &offsets[0], GL_DYNAMIC_DRAW);
	
}

void ParticleSystem::Reset()
{
	RESET = true;
}

void ParticleSystem::Draw()
{
	RESET = false;
	glBindVertexArray(m_vertexArrayObject);

	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, numParticles);

	glBindVertexArray(0);
}

float ParticleSystem::RandomFloat()
{
	return (float)rand() / ((float)RAND_MAX + 1);
}

