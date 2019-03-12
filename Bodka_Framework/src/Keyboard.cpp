#include "Keyboard.h"



Keyboard::Keyboard()
{
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_KEYS, 1);
	glfwPollEvents();
}


Keyboard::~Keyboard()
{
}



bool Keyboard::UP()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;

}

bool Keyboard::DOWN()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;
}

bool Keyboard::LEFT()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;
}

bool Keyboard::RIGHT()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;
}

bool Keyboard::SPACE()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;
}

bool Keyboard::ENTER()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ENTER);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;
		
}

bool Keyboard::W()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;
}

bool Keyboard::S()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;
}
bool Keyboard::A()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;
}

bool Keyboard::D()
{
	int state = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D);
	if (state == GLFW_PRESS)
	{
		return true;
		state = GLFW_RELEASE;
	}
	else
		return false;
}


void Keyboard::Control::FrontMove(Transform & transform,float speed)
{
	transform.GetPos().z += speed * cos(transform.GetRot().y);
	transform.GetPos().x += speed * sin(transform.GetRot().y);

}

void Keyboard::Control::BackMove(Transform & transform, float speed)
{
	transform.GetPos().z -= speed * cos(transform.GetRot().y);
	transform.GetPos().x -= speed * sin(transform.GetRot().y);
}

void Keyboard::Control::LeftRotation(Transform & transform)
{
	if (transform.GetRot().y >= 2 * pi)
	{
		transform.GetRot().y = 0.0;
		transform.rot = 0;
	}
	transform.GetRot().y += 0.005;
	if (transform.rot <= transform.maxRotSize)
	{
		transform.rot += transform.maxRotSize / 1200;
	}
	
}

void Keyboard::Control::RightRotation(Transform & transform)
{
	if (transform.GetRot().y <= -pi)
	{
		transform.GetRot().y = pi;
		transform.rot = 0.009;
	}
	if (transform.GetRot().y < -2*pi)
	{
		transform.GetRot().y = 0;
		transform.rot = 0;
	}
	transform.GetRot().y -= 0.005;
	if (transform.rot >= -transform.maxRotSize)
	{
		transform.rot -= transform.maxRotSize / 1200;
	}
	
}
