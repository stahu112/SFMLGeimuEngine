#include "Playing_State.h"
#include "Menu_State.h"
#include "../SFMLDebugDraw.h"

#include <fstream>
#include <math.h>
#include <iostream>

SFMLDebugDraw debugDraw;

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
		world = new b2World(b2Vec2(0.f, 10.f));
		//world->ShiftOrigin(b2Vec2(0, 0));
		player = new Character_Candy(*this);
		initLevels();
		changeLevel(LevelID::level1);
		world->SetDebugDraw(&debugDraw);
		debugDraw.SetFlags(b2Draw::e_shapeBit);
		//currentLevel = &m_levels.at(LevelID::level0);
	}

	void Playing::initLevels()
	{
		Level level0(
			30,
			20,
			Texture_Name::test2,
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
			m_p_application->changeState(std::make_unique<Menu>(*m_p_application));
		}

		if (InputHandler::checkDown(sf::Keyboard::D))
		{
			player->getVelocity().x = 200;
		}
		else
		if (InputHandler::checkDown(sf::Keyboard::A))
		{
			player->getVelocity().x = -200;
		}
		else
		{
			player->getVelocity().x = 0;
		}
		if (InputHandler::checkDown(sf::Keyboard::Space))
		{
			player->getVelocity().y = -1;
		}

	}

	//Aktualizuj stany
	void Playing::update(float dt)
	{
		world->Step(dt, 10, 10);
		
		player->update(dt);

		updateLevel(dt);
	}


	//Rysuj obiekty UI
	void Playing::draw()
	{
		player->draw();
		world->DrawDebugData();
	}

	void Playing::resolveCollisions(float dt)
	{

	}

	
	void Playing::changeLevel(LevelID level)
	{
		currentLevel = &m_levels.at(level);
		world->SetGravity(currentLevel->gravity);
		
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

	Level * Playing::getCurrentLevel() const
	{
		return currentLevel;
	}

	Character * Playing::getPlayer() const
	{
		return player;
	}

	b2World * Playing::getWorld()
	{
		return world;
	}

}
