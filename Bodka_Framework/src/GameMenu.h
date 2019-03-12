#pragma once
#include <Windows.h>
#include <tchar.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>


class GameMenu
{
public:
	GameMenu();
	~GameMenu();

	void ReadMemoryMappedFile();
	bool Start();
private:
	int * pBuf;
	int startGame;
	int saveGame;
	int loadGame;
	int exit;

};

