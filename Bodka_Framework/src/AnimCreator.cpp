#include "AnimCreator.h"
//test commit


AnimCreator::AnimCreator(std::string heads, std::string bodys, std::string Leg)
{
	head.Init(heads);
	body.Init(bodys);
	Legs.Init(Leg);

	std::cout << Legs.GetCenter().x << std::endl;
}


AnimCreator::~AnimCreator()
{
	
}


void AnimCreator::Draw(Shader& shader,Camera& camera)
{
	
	head.transform.SetScale(glm::vec3(0.1, 0.1, 0.1));
	head.transform.GetPos().y = Legs.transform.GetPos().y;
	head.transform.GetPos().x = Legs.transform.GetPos().x;
	head.transform.GetPos().z = Legs.transform.GetPos().z;
	shader.Update(head.transform, camera);
	head.Draw();
	
	body.transform.SetScale(glm::vec3(0.1, 0.1, 0.1));
	body.transform.GetPos().y = Legs.transform.GetPos().y;
	body.transform.GetPos().x = Legs.transform.GetPos().x;
	body.transform.GetPos().z = Legs.transform.GetPos().z;
	shader.Update(body.transform, camera);
	body.Draw();
	
	
	Legs.transform.SetScale(glm::vec3(0.1, 0.1, 0.1));
	shader.Update(Legs.transform, camera);
	Legs.Draw();
}

void AnimCreator::MovePart(Shader& shader, Camera& camera, Mesh & mesh,float speed)
{
		
	mesh.transform.SetScale(glm::vec3(0.1, 0.1, 0.1));
	mesh.transform.GetPos().y = Legs.transform.GetPos().y;
	mesh.transform.GetPos().z += speed * cos(Legs.transform.GetRot().y);
	mesh.transform.GetPos().x += speed * sin(Legs.transform.GetRot().y);
	shader.Update(mesh.transform, camera);
	mesh.Draw();
}

void AnimCreator::RotatePartLeft(Mesh & mesh)
{
	if (mesh.transform.GetRot().y >= 2 * pi)
	{
		mesh.transform.GetRot().y = 0.0;
		mesh.transform.rot = 0;
	}
	mesh.transform.GetRot().y += 0.01;
	if (mesh.transform.rot <= mesh.transform.maxRotSize)
	{
		mesh.transform.rot += mesh.transform.maxRotSize / 1200;
	}
}

void AnimCreator::RotatePartRight(Mesh & mesh)
{
	if (mesh.transform.GetRot().y <= -pi)
	{
		mesh.transform.GetRot().y = pi;
		mesh.transform.rot = 0.009;
	}
	if (mesh.transform.GetRot().y < -2 * pi)
	{
		mesh.transform.GetRot().y = 0;
		mesh.transform.rot = 0;
	}
	mesh.transform.GetRot().y -= 0.01;
	if (mesh.transform.rot >= -mesh.transform.maxRotSize)
	{
		mesh.transform.rot -= mesh.transform.maxRotSize / 1200;
	}
	
}

void AnimCreator::RotateLeft()
{
	RotatePartLeft(head);
	RotatePartLeft(body);
	RotatePartLeft(Legs);
}

void AnimCreator::RotateRight()
{
	RotatePartRight(head);
	RotatePartRight(body);
	RotatePartRight(Legs);
}

void AnimCreator::Move(Shader& shader, Camera& camera, float speed)
{
	if (RotateL)
	RotateLeft();
	if (RotateR)
	RotateRight();
	
	
	if (Moving)
	{
		MovePart(shader, camera, Legs, speed);
		
		MovePart(shader, camera, head, speed);
		
		MovePart(shader, camera, body, speed);
		
		
	



	}
	else
	{
		moveSpeed -= 0.00001;
		if (moveSpeed <= 0)
		{
			moveSpeed = 0;
		}
		MovePart(shader, camera, Legs, moveSpeed);
		
		MovePart(shader, camera, head, moveSpeed);
		
		MovePart(shader, camera, body, moveSpeed);
		//Draw(shader, camera);
	}

}

void AnimCreator::SwapPartUp()
{
	PART--;

	if (PART < HEAD)
	{
		PART = 2;
	}


}

void AnimCreator::SwapPartDown()
{
	PART++;

	if (PART > LEGS)
	{
		PART = 0;
	}
}



void AnimCreator::Fly(ParticleSystem & jet, Shader& shader, Camera& camera,float dt)
{
	if (Flying)
	{
		jet.transform.GetPos().x = -sin(body.transform.GetRot().y) * 0.1 + body.transform.GetPos().x;
		jet.transform.GetPos().z = -cos(body.transform.GetRot().y) * 0.1 + body.transform.GetPos().z;
		jet.transform.GetPos().y = body.transform.GetPos().y + 0.18;

		jet.transform.GetRot().y = body.transform.GetRot().y;
		jet.transform.SetScale(glm::vec3(0.1, 0.1, 0.1));
		
		shader.Update(jet.transform, camera);
		jet.Update(dt,shader);
		jet.Draw();

		
		if (flySpeed < 10)
		{
			flySpeed += 1.5 * dt;
		}
		Legs.transform.GetPos().y += 0.001 * flySpeed;

		if (Moving)
		{
			if (moveSpeed < 0.01)
			{
				moveSpeed += 0.0005;
			}
		}
		
		
	}
	else
	{
		if (flySpeed > -5)
		{
			flySpeed -= 2 * dt;
		}
		Legs.transform.GetPos().y += 0.001 * flySpeed;
		
			
		
	}
	

}



Mesh& AnimCreator::ReturnPart()
{
	if (PART == HEAD)
	{
		return head;
	}

	if (PART == BODY)
	{
		return body;
	}

	if (PART == LEGS)
	{
		return Legs;
	}
}


