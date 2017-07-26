#include "Application.h"



Application::Application()
{
	Display::init();
}


Application::~Application()
{
}

void Application::runMainLoop()
{
	while (Display::isOpen())
	{
		Display::checkWindowEvents();

		Display::clear();

		//input
		//update
		//draw

		Display::display();
	}
}
