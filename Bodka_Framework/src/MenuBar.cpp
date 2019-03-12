#include "MenuBar.h"



MenuBar::MenuBar(Window& wnd)
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(wnd.GetWindow(), true);
	ImGui::StyleColorsDark();
}


MenuBar::~MenuBar()
{
}

void MenuBar::InitImGuiWin()
{
	ImGui_ImplGlfwGL3_NewFrame();

	ImGui::Text("Bodka_Engine");



	StartButton();
	SaveButton();
	LoadButton();
	

	
	
	



	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

}



void MenuBar::Terminate()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void MenuBar::StartButton()
{
	if (ImGui::Button("START GAME"))
	{
		StartGame = true;
	}
	
}

void MenuBar::SaveButton()
{
	if (ImGui::Button("SAVE"))
	{
		save = true;
	}
	else
		save = false;
}

void MenuBar::LoadButton()
{
	if (ImGui::Button("LOAD"))
	{
		load = true;
	}
	else
		load = false;
}

