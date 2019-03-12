#include "GameMenu.h"



GameMenu::GameMenu()
{
}


GameMenu::~GameMenu()
{
}

void GameMenu::ReadMemoryMappedFile()
{
	HANDLE hMapFile;

	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		"startmenu");

	if (hMapFile == NULL)
	{
		//_tprintf(TEXT("Could not open file"));
		//GetLastError();

		CloseHandle(hMapFile);
		
	}

	pBuf = (int*)MapViewOfFile(hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		256);
	
	
	if (!pBuf == NULL)
	{
		startGame = *pBuf;
	}
	
}

bool GameMenu::Start()
{
	
	return startGame;
}
