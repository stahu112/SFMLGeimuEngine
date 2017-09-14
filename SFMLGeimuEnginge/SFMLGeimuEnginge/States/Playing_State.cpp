#include "Playing_State.h"

#include <fstream>

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

	void Playing::initLevels()
	{
		Level level0(
			40,
			40,
			Texture_Name::test2,
			false,
			*this
		);

		/*Level level1(
			Texture_Name::test,
			Texture_Name::tilemap,
			"Resources/level.txt",
			"Resources/levelCol.txt",
			false,
			*this
		);*/

		addLevel(LevelID::level0, level0);
		//addLevel(LevelID::level1, level1);
	}

	//Sterowanie itp.
	void Playing::input()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player->goalVelocity.x = 200;
		if (InputHandler::checkUp(sf::Keyboard::D)) player->goalVelocity.x = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player->goalVelocity.y = -200;
		if (InputHandler::checkUp(sf::Keyboard::W)) player->goalVelocity.y = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player->goalVelocity.y = 200;
		if (InputHandler::checkUp(sf::Keyboard::S)) player->goalVelocity.y = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player->goalVelocity.x = -200;
		if (InputHandler::checkUp(sf::Keyboard::A)) player->goalVelocity.x = 0;

	}

	//Aktualizuj stany
	void Playing::update(float dt)
	{
		updateLevel(dt);

		player->update(dt);

		resolveCollisions(dt);
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
