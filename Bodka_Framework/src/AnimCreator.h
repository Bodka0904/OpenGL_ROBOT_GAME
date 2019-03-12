#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include <string>
#include <glm/glm.hpp>
#include <iostream>
#include "ParticleSystem.h"



class AnimCreator
{
public:
	AnimCreator(std::string heads, std::string bodys, std::string Leg);
	~AnimCreator();

	void Draw(Shader& shader, Camera& camera);
	void MovePart(Shader& shader, Camera& camera, Mesh& mesh,float speed);
	void RotatePartLeft( Mesh& mesh);
	void RotatePartRight( Mesh& mesh);

	void RotateLeft();
	void RotateRight();
	void Move(Shader& shader, Camera& camera, float speed);
	
	void SwapPartUp();
	void SwapPartDown();
	
	void Fly(ParticleSystem& jet,Shader& shader,Camera& camera,float dt);
	Mesh& ReturnPart();

public:
	Mesh head;
	Mesh body;
	Mesh Legs;
	
private:
	float RotX;
	float RotZ;
	
	static constexpr float pi = 3.141592653589793238;
	float count = 0;
	float flySpeed = 0;
	float moveSpeed = 0;
	
private:
	enum RotationPart
	{
		HEAD,

		BODY,

		LEGS

	};
	int PART = 0;

public:
	bool Moving = false;
	bool Flying = false;
	bool RotateL = false;
	bool RotateR = false;


}; 

