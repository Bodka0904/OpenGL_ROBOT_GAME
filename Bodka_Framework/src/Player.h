#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "Keyboard.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>



class Player
{
public:
	Player();
	~Player();
	
	void Init();
	void AnimLoader(std::string filename,unsigned int num);
	void Draw();
	void Walk(float speed,float timeF,Keyboard& kbd);
	void Flight(float speed, float timeF, Keyboard& kbd);
	
	
	

public:
	Mesh mesh[100];
private:
	int curFrame = 1;
	float count = 0.0f;

	int walkF = 1;
	int prepareToFlightF = 40;
	int flightF = 80;
	int landF = 90;

	bool UpF;
	bool DownF;

	bool walking = true;
	
	bool flight = false;
	

};

