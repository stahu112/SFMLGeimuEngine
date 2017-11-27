#include "Playing_State.h"
#include "Menu_State.h"
#include "../SFMLDebugDraw.h"
#include "../MyColCallback.h"

#include <fstream>
#include <math.h>
#include <iostream>

#define DEBUGMODE true

SFMLDebugDraw debugDraw;
MyColCallback colCall;

namespace State
{
	//Inicjuj STATE, testowo potworzone rozne obiekty, przypisane tekstury, dzwieki itp
	Playing::Playing(Application & application)
		: Game_State(application)
	{
		initState();
		colCall.state = this;
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
		changeLevel(LevelID::level0);
		world->SetDebugDraw(&debugDraw);
		debugDraw.SetFlags(b2Draw::e_shapeBit);
		world->SetContactListener(&colCall);
		//currentLevel = &m_levels.at(LevelID::level0);
	}

	void Playing::initLevels()
	{
		Level level0(
			50,
			20,
			Texture_Name::test2,
			false,
			*this
		);

		level0.loadLevel("lev0.txt");

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
		if(DEBUGMODE) world->DrawDebugData();
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
