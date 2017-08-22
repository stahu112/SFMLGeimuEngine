#include "Playing_State.h"

#include <iostream>

namespace State
{
	//Inicjuj STATE, testowo potworzone rozne obiekty, przypisane tekstury, dzwieki itp
	Playing::Playing(Application & application)
		: Game_State(application)
	{
		initState();
	}

	//Sterowanie itp.
	void Playing::input()
	{
	}

	//Aktualizuj stany
	void Playing::update(float dt)
	{
		void processLevel();
		chara.update(dt);
	}

	//Rysuj obiekty
	void Playing::draw()
	{
	
	}

	void Playing::initState()
	{
		Level level0;
		level0.test = 1;
		m_levels.insert(std::make_pair(LevelID::level0, level0));

		changeLevel(LevelID::level0);
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