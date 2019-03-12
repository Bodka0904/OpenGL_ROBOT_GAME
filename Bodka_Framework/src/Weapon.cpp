#include "Weapon.h"



FireBalls::FireBalls()
	:
	ball("res/models/weaponball.obj")
{
}

void FireBalls::SetFireBall(Transform& transform)
{
	ball.transform.GetPos() = transform.GetPos();
	
}

void FireBalls::FireFireBall(Transform & transform)
{
	
	if (fired)
	{
		
		ball.transform.GetPos().z += m_speed * cos(m_direction.y);
		ball.transform.GetPos().x += m_speed * sin(m_direction.y);
		
		DrawFireBall(ball);
		readyToFire = false;
	}
	
}

void FireBalls::Fire(Transform& transform)
{

	if (readyToFire)
	{
		m_direction = glm::vec3(transform.GetRot().x, transform.GetRot().y, transform.GetRot().z);
		SetFireBall(transform);
	}
	fired = true;
	readyToFire = false;
}

void FireBalls::DrawFireBall(Mesh & object)
{
	object.Draw();
	ball.transform.SetScale(glm::vec3(0.01, 0.01, 0.01));
	ball.transform.GetRot().x += 0.02;
	ball.transform.GetRot().y += 0.02;
	ball.transform.GetRot().z += 0.02;
}

void FireBalls::CheckIfOutOfGrid(Grid & grid)
{
	if (abs(ball.transform.GetPos().x) > (grid.GetGridSize() / 20 + grid.GetGridCenter()) || abs(ball.transform.GetPos().z) > (grid.GetGridSize() / 20 + grid.GetGridCenter()))
	{
		fired = false;
		readyToFire = true;

	}
}


