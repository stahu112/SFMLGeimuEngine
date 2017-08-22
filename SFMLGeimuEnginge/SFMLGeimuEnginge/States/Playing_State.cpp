#include "Playing_State.h"

#include <iostream>

namespace State
{
	//Inicjuj STATE, testowo potworzone rozne obiekty, przypisane tekstury, dzwieki itp
	Playing::Playing(Application & application)
		: Game_State(application)
	{
	}

	//Sterowanie itp.
	void Playing::input()
	{
	}

	//Aktualizuj stany
	//TODO liczyc dt, liczenie klatek itp.
	void Playing::update(float dt)
	{
	}

	//Rysuj obiekty
	void Playing::draw()
	{
		std::cout << "Playing" << std::endl;
	}

}