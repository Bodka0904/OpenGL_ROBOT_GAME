#pragma once
#include "Window.h"
#include <fstream>
#include <string>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw_gl3.h"

class MenuBar
{
public:
	MenuBar(Window& wnd);
	~MenuBar();

	void InitImGuiWin();
	void Terminate();
	void StartButton();
	void SaveButton();
	void LoadButton();

	

public:
	bool StartGame = false;
	bool save = false;
	bool load = false;

	
		
};

