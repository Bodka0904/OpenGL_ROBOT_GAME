#include "src\Game.h"
#include "SDL.h"

int main(int argc, char*argv[])
{

	Game game;



	while (!game.wnd.IsClosed())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game.menu.InitImGuiWin();
		game.Go();
		game.wnd.Update();

	}

	game.menu.Terminate();
	game.wnd.Terminate();
	return 0;
}

