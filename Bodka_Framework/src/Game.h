#pragma once
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Keyboard.h"
#include "obj_loader.h"
#include "SaveLoadSystem.h"
#include "MenuBar.h"
//#include "Player.h"
#include "FrameTimer.h"
#include <fstream>
#include "GameMenu.h"
#include "AnimCreator.h"
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include "ParticleSystem.h"
#include "PlanetarySystem.h"
#include "Terrain.h"





class Game
{
public:
	Game();
	void Setup();
	void Go();
	

	Window wnd;
	MenuBar menu;

public:
	//SaveLoadSystem numOfObjects can not be lower
	
	
private:
	//Default
	
	Shader shader;
	Transform transform;

	Camera camera;
	GameMenu menubar;
	//Board brd;
	
	

	Keyboard kbd;
	

	//Optional
	
	//Player player;
	Terrain ter;
	Planet planet; //must be initialized earlier as anim because of particle system.
	AnimCreator anim;
	ParticleSystem jet;
	ParticleSystem core;

	

	
	
	
	
	
	Texture texture;
	Texture grassT;
	FrameTimer ft;

	
	

	Save save;
	Load load;

private:
	int curFrame = 1;
	float dt = 0;
	float count = 0;

	

	bool Up = false;
	bool Down = false;


	bool FLY = false;
	bool WALK = false;
	int show = 0;

	
};

