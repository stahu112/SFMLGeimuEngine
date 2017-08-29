#include "Playing_State.h"

#include <iostream>

static Character_Candy Candy;

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
		setPlayer(&Candy);
		initLevels();
		changeLevel(LevelID::level0);
	}

	Level * Playing::getCurrentLevel() const
	{
		return currentLevel;
	}

	Character * Playing::getPlayer() const
	{
		return player;
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
		getPlayer()->update(dt);
		
		if (InputHandler::checkJDown(8))
		{
			std::cout << "1 Pressed" << std::endl;
		}
		if (InputHandler::checkJUp(9))
		{
			std::cout << "1 Released" << std::endl;
		}

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
			currentLevel->drawLevel();
			currentLevel->setView();
		}
	}

	//AddLevel
	void Playing::addLevel(LevelID id, Level level)
	{
		m_levels.insert(std::make_pair(id, level));
	}

	void Playing::initLevels()
	{
		Level level0(
			Texture_Name::test2,
			sf::Vector2u(10,10),
			false,
			*this
		);
		addLevel(LevelID::level0, level0);
	}

	void Playing::setPlayer(Character * chara)
	{
		player = chara;
	}

}
