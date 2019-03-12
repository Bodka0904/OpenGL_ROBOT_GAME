#include "Window.h"


Window::Window(int width, int height, const char* title)
{
	
	m_width = width;
	m_height = height;
	m_title = title;
	Init();

	glewInit();
	
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	
}


Window::~Window()
{
	glfwTerminate();
}

void Window::Init()
{

	if(!glfwInit())
	{
		std::cout << "Error" << std::endl;
		glfwTerminate();
	}

	m_window = glfwCreateWindow(m_width,m_height,m_title,NULL, NULL);
	
	glfwMakeContextCurrent(m_window);
	glfwWindowHint(GLFW_DEPTH_BITS, 16);
	
	
	
}

void Window::Update() const
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

bool Window::IsClosed()
{
	return glfwWindowShouldClose(m_window);
}


void Window::Terminate()
{
	glfwTerminate();
}

void Window::ShowWindow()
{
	glfwShowWindow(m_window);
}




unsigned int Window::GetWidth() const
{
	return m_width;
}

unsigned int Window::GetHeight() const
{
	return m_height;
}

GLFWwindow * Window::GetWindow() const
{
	return m_window;
}
