//#########################
//#MICHAL STANKIEWICZ 2017#
//#########################

//MAIN

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>

#include "Application.h"

int main()
{
	//Tworzysz obiekt aplikacji "app"
	Application app;

	//Glowna petla
	app.runMainLoop();

	return EXIT_SUCCESS; 
}