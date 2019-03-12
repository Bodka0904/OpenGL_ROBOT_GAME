#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
	
}

void Player::Init()
{
	AnimLoader("res/models/player/player", 100);
}

void Player::AnimLoader(std::string filename, unsigned int num)
{
	char tmp[200];

	for (int i = 2; i <= num; i++)
	{
		if (i < 10)
		{
			sprintf_s(tmp, "_00000%d", i);
		}
		else if (i < 100)
		{
			sprintf_s(tmp, "_0000%d", i);
		}
		else if (i < 1000)
		{
			sprintf_s(tmp, "_000%d", i); //Finish later
		}

		std::string tmp2(filename + tmp);
		tmp2 += ".obj";

		
		mesh[i-1].Init(tmp2);

		
	}
	
}

void Player::Draw()
{
	mesh[curFrame].Draw();
}

void Player::Walk(float speed, float timeF,Keyboard& kbd)
{
	if (flight)
	{
		UpF = false;
		DownF = false;
		if (curFrame <= 90 && curFrame > 40)
		{
			count += timeF;
			if (count > 0.01)
			{
				curFrame++;
				count = 0;
			}
		
		}
		else if (curFrame >= 90 && curFrame < 100)
		{
			count += timeF;
			if (count > 0.06)
			{
				curFrame++;
				count = 0;
			}
		}
		if (curFrame == 99)
		{
			curFrame = 1;
			flight = false;
			walking = true;
		}
	}
	
	
	

	if (walking)
	{
		for (int i = 1; i < 100; i++)
		{
			kbd.ctrl.FrontMove(mesh[i].transform, speed);
		}
		count += timeF;

	}
	if (curFrame == prepareToFlightF - 1)
	{
		UpF = false;
		DownF = true;
		curFrame = 20;
	}
	if (curFrame == walkF)
	{
		UpF = true;
		DownF = false;
		curFrame = 20;
	}
	if (count > 0.03)
	{
		if (UpF)
		{
			curFrame++;
			count = 0;
		}
		if (DownF)
		{
			curFrame--;
			count = 0;

		}

	}
	
}

void Player::Flight(float speed, float timeF, Keyboard & kbd)
{
	if (walking)
	{
		curFrame = 40;
	}
	walking = false;
	flight = true;
	

	if (flight)
	{
		count += timeF;
		if (curFrame <= 80)
		{
			if (count > 0.06)
			{
				curFrame++;
				count = 0;
			}
		}
		if(curFrame >= 80)
		{
			for (int i = 1; i < 100; i++)
			{
				kbd.ctrl.FrontMove(mesh[i].transform, speed);
			}

			if (curFrame == landF - 1)
			{
				UpF = false;
				DownF = true;
			}
			if (curFrame == flightF)
			{
				UpF = true;
				DownF = false;
			}
			if (count > 0.01)
			{
				if (UpF)
				{
					curFrame++;
					count = 0;
				}
				if (DownF)
				{
					curFrame--;
					count = 0;

				}

			}

		}
	}
	
}






