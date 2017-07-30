//#########################
//#MICHAL STANKIEWICZ 2017#
//#########################

//Na razie dosc prosty silnik do gier 2D na podstawie biblioteki SFML
//TODO Zmienic baze na SFML/OpenGL to wtedy 3D tez

//MAIN

#include <iostream>

#include "Application.h"

int main()
{
	//Tworzysz obiekt aplikacji "app"
	Application app;

	//Glowna petla
	app.runMainLoop();

	return EXIT_SUCCESS; //Makro z iostream "0"
}