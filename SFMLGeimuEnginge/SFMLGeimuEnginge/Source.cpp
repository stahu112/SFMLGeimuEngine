//#########################
//#MICHAL STANKIEWICZ 2017#
//#########################

//Na razie dosc prosty silnik do gier 2D na podstawie biblioteki SFML
//TODO Jak sie ogarnie opengl to 3D

//MAIN

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