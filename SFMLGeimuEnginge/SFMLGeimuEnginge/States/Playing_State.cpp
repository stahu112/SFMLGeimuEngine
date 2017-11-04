#include "Playing_State.h"
#include "Menu_State.h"

#include <fstream>
#include <math.h>
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
	
	void Playing::reInit()
	{
	}

	void Playing::initState()
	{
		setPlayer(&Candy);
		initLevels();
		changeLevel(LevelID::level1);
		//currentLevel = &m_levels.at(LevelID::level0);
	}

	void Playing::initLevels()
	{
		Level level0(
			30,
			20,
			Texture_Name::test,
			false,
			*this
		);

		Level level1(
			50,
			20,
			Texture_Name::test1,
			false,
			*this
		);

		addLevel(LevelID::level0, level0);
		addLevel(LevelID::level1, level1);
	}

	//Sterowanie itp.
	void Playing::input()
	{
		if (InputHandler::checkDown(sf::Keyboard::Escape))
		{
			m_p_application->popState();
		}

		if (InputHandler::checkDown(sf::Keyboard::D))
		{
			player->goalVelocity.x = 200;
		}
		else
		if (InputHandler::checkDown(sf::Keyboard::A))
		{
			player->goalVelocity.x = -200;
		}
		else
		{
			player->goalVelocity.x = 0;
		}
	}

	//Aktualizuj stany
	void Playing::update(float dt)
	{
		player->update(dt);

		updateLevel(dt);
	}


	//Rysuj obiekty UI
	void Playing::draw()
	{
		player->draw();
	}

	void Playing::resolveCollisions(float dt)
	{

	}

	
	void Playing::changeLevel(LevelID level)
	{
		currentLevel = &m_levels.at(level);
		player->setPosition(m_levels.at(level).startingPosition);
	}

	void Playing::updateLevel(float dt)
	{
		if (currentLevel)
		{
			currentLevel->drawLevel();
			currentLevel->setView(dt);
		}
	}

	//AddLevel
	void Playing::addLevel(LevelID id, Level level)
	{
		m_levels.insert(std::make_pair(id, level));
	}

	void Playing::setPlayer(Character * chara)
	{
		player = chara;
	}

	Level * Playing::getCurrentLevel() const
	{
		return currentLevel;
	}

	Character * Playing::getPlayer() const
	{
		return player;
	}
}
