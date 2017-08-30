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
		currentLevel->getPlatforms()->emplace_back(sf::Vector2f(0, currentLevel->getSize().y * currentLevel->tileSize.x), sf::Vector2f(currentLevel->getSize().x * currentLevel->tileSize.x, 8), Texture_Name::test);

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

		if (getPlayer()->getFlags().onGround)
		{
			if (!getPlayer()->getFlags().dashing)
			{
				getPlayer()->setVelocity(sf::Vector2f(
					InputHandler::getAxisPosition(sf::Joystick::Axis::X),
					getPlayer()->getVelocity().y
				));
			}

			if (InputHandler::checkJDown(10)) { getPlayer()->getFlags().dashing = true; getPlayer()->dash(); }
			else if (InputHandler::getAxisPosition(sf::Joystick::Axis::X)
				< InputHandler::deadZone &&
				InputHandler::getAxisPosition(sf::Joystick::Axis::X)
				> -InputHandler::deadZone)
			{
				getPlayer()->getFlags().dashing = false;
			}
		}

		if (InputHandler::checkJDown(1)) getPlayer()->jump();

		if (Collision::collisionWithPlat(
			getPlayer(),
			HitId::L,
			currentLevel->getPlatforms()->at(0),
			HitIdPlat::baseU))
		{
			getPlayer()->getFlags().onGround = true;
			getPlayer()->setPosition(sf::Vector2f(
				getPlayer()->getPosition().x,
				currentLevel->getPlatforms()->at(0).getPosition().y - getPlayer()->getSize().y
			));
		}
		std::cout << (int)getPlayer()->getCurrentState() << std::endl;

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
