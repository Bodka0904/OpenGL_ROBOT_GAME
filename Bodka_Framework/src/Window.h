#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>


class Window
{
public:
	Window(int width,int height,const char* title);
	virtual~Window();
	void Init();
	void Update() const;
	bool IsClosed();
	void Terminate();
	void ShowWindow();
	
	

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	GLFWwindow* GetWindow() const;
private:
	GLFWwindow * m_window;
	
	unsigned int m_width;
	unsigned int m_height;
	const char* m_title;

};

