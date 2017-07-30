#include "Playing_State.h"

#include <iostream>

namespace State
{
	//Inicjuj STATE, testowo potworzone rozne obiekty, przypisane tekstury, dzwieki itp
	Playing::Playing(Application & application)
		: Game_State(application)
	{
		//Obiekt MUSIC w przeciwienstwie do obiektu SOUND, czyta plik bezposrednio z dysku zeby zaoszczedzic miejsce
		//Dlatego nie robilem dla niego managera
		music.openFromFile("Resources/Sound/yam.ogg");
		music.play();

	}

	//Sterowanie itp.
	void Playing::input()
	{

	}

	//Aktualizuj stany
	//TODO liczyc dt, liczenie klatek itp.
	void Playing::update(float dt)
	{
		player.update(dt);
	}

	//Rysuj obiekty
	void Playing::draw()
	{
		Display::draw(player.shape);
	}

}