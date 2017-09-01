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
		player->setPosition(sf::Vector2f(0, 0));
		initLevels();
		changeLevel(LevelID::level0);
	}

	void Playing::initLevels()
	{
		Level level0(
			Texture_Name::test2,
			sf::Vector2u(100, 50),
			false,
			*this
		);

		//TODO zgranie z pliku
		level0.getPlatforms()->emplace_back(
			sf::Vector2f(0, level0.getSize().y * level0.tileSize.y),
			sf::Vector2f(level0.getSize().x * level0.tileSize.x, level0.tileSize.y),
			Texture_Name::test);

		level0.getPlatforms()->emplace_back(sf::Vector2f(
			level0.tileSize.x * 2, level0.getSize().y*level0.tileSize.x - level0.tileSize.y * 2),
			sf::Vector2f(level0.tileSize.x * 10, level0.tileSize.y),
			Texture_Name::test);

		addLevel(LevelID::level0, level0);

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
