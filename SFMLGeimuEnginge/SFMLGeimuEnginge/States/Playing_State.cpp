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
	void Playing::update(float dt)
	{
		void processLevel();
	}

	//Rysuj obiekty
	void Playing::draw()
	{
		std::cout << "Playing" << std::endl;
	}

	void Playing::changeLevel(LevelID level)
	{
		currentLevel = &m_levels.at(level);
	}

	void Playing::processLevel()
	{
		//TODO Jesli cos tam to zmien level na jakis tam np. jesli wlezie na teleport do levelu las to zmien currentlevel na level las itd.
	}

}