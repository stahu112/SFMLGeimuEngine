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
		getPlayer()->getBaseStats().ID = "cos";
		std::cout << getPlayer()->getBaseStats().ID << " " << getPlayer()->getPosition().y << std::endl;
		getPlayer()->update(dt);
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
			sf::Vector2u(200,10),
			level0des,
			false
		);
		addLevel(LevelID::level0, level0);
		level0.setPlayerHandle(*this);
	}

	void Playing::setPlayer(Character * chara)
	{
		player = chara;
	}

}
