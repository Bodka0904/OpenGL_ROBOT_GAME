#include "Game.h"



Game::Game()
	:
	wnd(1200, 1200, "Bodka_Engine"),
	menu(wnd),
	shader("res/basicShader"),
	camera(glm::vec3(0, 0.5, -2), 70.0f, (wnd.GetWidth() / wnd.GetHeight()), 0.01f, 1000.0f),
	texture("res/textures/robotTex.jpg"),
	grassT("res/textures/grass.jpg"),
	save("data.txt"),
	load("data.txt"),
	ter("res/heightmap/heightMap.bmp", 0.5, 10,glm::vec3(0.4, 0.5, 0.7)),
	planet(5, 0,glm::vec3(0.4,0.7,1)),
	anim("res/models/body/head.obj", "res/models/body/body.obj", "res/models/body/Legs.obj"),
	jet(1000, -2, 0, 0.02,glm::vec3(1,0.8,0.7), JET),
	core(5000, 0, 3, 0.1,glm::vec3(0.3,0.2,1), CORE)

	

	
	
{
	//player.Init
	planet.GetRadius();

	
}

void Game::Setup()
{
	
	shader.Bind();
	

	
	
	
	

	

	/////////MODELS CONFIGURATION/////////
	////////////ROBOT/////////////////////
	camera.CameraFollow(anim.head.transform);
	texture.Bind(0);
	anim.Move(shader, camera, 0.01);
	anim.Fly(jet, shader, camera,dt);

	/////////////////////////////////////
	//////////////PLANET/////////////////
	planet.Move(glm::vec3(ter.GetSize() / 2, 2, ter.GetSize() / 2), 50, 1, shader, camera);
	planet.Draw();


	core.transform.SetPos(glm::vec3(planet.transform.GetPos().x, planet.transform.GetPos().y, planet.transform.GetPos().z));
	shader.Update(core.transform, camera);
	core.Update(dt,shader);
	core.Draw();
	
	///////////////////////////////////////
	////////////////TERRAIN////////////////

	ter.Draw(shader, camera);
	ter.Collision(anim.Legs.transform);

	///////////////////////////////////////
	
	


	
	
	
	
	
	

	dt = ft.Mark();
}

void Game::Go()
{
	menubar.ReadMemoryMappedFile();

	//Game Loop//

	if(true)//(menubar.Start())
	{
		Setup();
		

		if (kbd.UP())
		{
			anim.Moving = true;

		}
		else
			anim.Moving = false;

		if (kbd.DOWN())
		{
			anim.Flying = true;

		}
		else 
		{
			anim.Flying = false;
			jet.Reset();
		};

		if (kbd.LEFT())
		{
			anim.RotateL = true;
			
		}
		else
			anim.RotateL = false;
		
		
		if (kbd.RIGHT())
		{
			anim.RotateR = true;

		}
		else
			anim.RotateR = false;

		if (kbd.SPACE() )
		{
			planet.Destroy();
			core.Explode();
		}

		



		if (kbd.W())
		{
			anim.SwapPartUp();
		}
		if (kbd.S())
		{
			anim.SwapPartDown();
		}
		if (kbd.A())
		{
			anim.RotatePartLeft(anim.ReturnPart());
		}
		if (kbd.D())
		{
			anim.RotatePartRight(anim.ReturnPart());
		}


		if (menu.save)
		{
			//save.FreeMemory();
			//for (int i = 0; i < numOfMonkeys; ++i)
			//{
			//	save.UpdateObjects(monkey[i].transform);
			//}
			//save.SaveAll();
		}
		if (menu.load)
		{
			//load.LoadLastGame();
			//for (int i = 0; i < numOfMonkeys; ++i)
			//{
			//	load.UpdateObjects(monkey[i].transform);
			//}

		}
	}
	
}




