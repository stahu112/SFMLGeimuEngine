#include "Playing_State.h"

#include <cmath>

#define macDEFINE_FLOOR sf::Vector2f(0, currentLevel->getSize().y * currentLevel->tileSize.y), sf::Vector2f(currentLevel->getSize().x * currentLevel->tileSize.x, currentLevel->tileSize.y)

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
//TODO zgranie z pliku
		currentLevel->getPlatforms()->emplace_back(macDEFINE_FLOOR, Texture_Name::test);

		currentLevel->getPlatforms()->emplace_back(sf::Vector2f(
			currentLevel->tileSize.x*2, currentLevel->getSize().y*currentLevel->tileSize.x - currentLevel->tileSize.y*2),
			sf::Vector2f(currentLevel->tileSize.x * 10, currentLevel->tileSize.y),
			Texture_Name::test);
	}

	Level * Playing::getCurrentLevel() const
	{
		return currentLevel;
	}

	Character * Playing::getPlayer() const
	{
		return player;
	}

	//Sterowanie itp.
	void Playing::input()
	{
	
	}

	//Aktualizuj stany
	void Playing::update(float dt)
	{
		updateLevel();
		player->update(dt);

		resolveCollisions();
	}


	//Rysuj obiekty UI
	void Playing::draw()
	{
		player->draw();
	}

	void Playing::resolveCollisions()
	{
		
	}
	

	
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
			sf::Vector2u(100,50),
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
