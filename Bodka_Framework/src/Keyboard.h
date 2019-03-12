#pragma once
#include <math.h>
#include <iostream>
#include "Transform.h"
#include "GLFW/glfw3.h"

class Keyboard
{
public:
	Keyboard();
	~Keyboard();
	
	//control keys
	bool UP();
	bool DOWN();
	bool LEFT();
	bool RIGHT();
	
	

	bool W();
	bool S();
	bool A();
	bool D();
	bool SPACE();


	//special keys
	bool ENTER();
	
public:
	class Control
	{
	public:
		Control() = default;
		void FrontMove(Transform& transform,float speed);
		void BackMove(Transform& transform, float speed);
		void LeftRotation(Transform& transform);
		void RightRotation(Transform& transform);


	};
public:
	Control ctrl;
	static constexpr float pi = 3.14159;
	

	

};

