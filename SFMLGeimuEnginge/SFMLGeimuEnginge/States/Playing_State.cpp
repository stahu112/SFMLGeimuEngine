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

	void Playing::initState()
	{
		initLevels();
		changeLevel(LevelID::level0);
	}

	Level * Playing::getCurrentLevel() const
	{
		return currentLevel;
	}


	//############################################
	//############################################
	//############################################

	//Sterowanie itp.
	void Playing::input()
	{
	}

	//Aktualizuj stany
	void Playing::update(float dt)
	{
		updateLevel();
	}

	//Rysuj obiekty
	void Playing::draw()
	{
		
	}
	
	//############################################
	//############################################
	//############################################
	
	void Playing::changeLevel(LevelID level)
	{
		currentLevel = &m_levels.at(level);
	}

	void Playing::updateLevel()
	{
		if (currentLevel)
		{
			currentLevel->setView();

			//DRAW
			currentLevel->drawLevel();
		}
	}

	//AddLevel
	void Playing::addLevel(LevelID id, Level level)
	{
		m_levels.insert(std::make_pair(id, level));
	}

	void Playing::initLevels()	//TODO Wczytywac levele z pliku
	{
		Level level0(
			Texture_Name::tileset,
			Texture_Name::test2,
			sf::Vector2u(10,5),
			level0des,
			false
		);
		addLevel(LevelID::level0, level0);
	}

}
