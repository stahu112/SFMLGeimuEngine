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
			sf::Vector2u(60, 30),
			false,
			*this
		);

		//TODO zgranie z pliku
		level0.getPlatforms()->emplace_back(
			sf::Vector2f(0, level0.getSize().y * level0.tileSize.y),
			sf::Vector2f(level0.getSize().x * level0.tileSize.x, level0.tileSize.y*10),
			Texture_Name::test);

		level0.getPlatforms()->emplace_back(sf::Vector2f(
			0, level0.getSize().y*level0.tileSize.x - level0.tileSize.y * 4),
			sf::Vector2f(level0.tileSize.x * 10, level0.tileSize.y),
			Texture_Name::test);

		level0.getPlatforms()->emplace_back(sf::Vector2f(
			level0.tileSize.x * 2, level0.getSize().y*level0.tileSize.x - level0.tileSize.y * 8),
			sf::Vector2f(level0.tileSize.x * 10, level0.tileSize.y),
			Texture_Name::test);

		level0.getPlatforms()->emplace_back(sf::Vector2f(
			0, level0.getSize().y*level0.tileSize.x - level0.tileSize.y * 12),
			sf::Vector2f(level0.tileSize.x * 10, level0.tileSize.y),
			Texture_Name::test);

		level0.getPlatforms()->emplace_back(sf::Vector2f(
			level0.tileSize.x * 2, level0.getSize().y*level0.tileSize.x - level0.tileSize.y * 16),
			sf::Vector2f(level0.tileSize.x * 10, level0.tileSize.y),
			Texture_Name::test);
		addLevel(LevelID::level0, level0);

	}

	//Sterowanie itp.
	void Playing::input()
	{
		if (InputHandler::checkDown(sf::Keyboard::Space))
		{
			player->getFlags().inAir = true;
			player->getVelocity().y = -100;
		}

		if (InputHandler::checkDown(sf::Keyboard::Right)) player->getVelocity().x = 250;
		if (InputHandler::checkUp(sf::Keyboard::Right)) player->getVelocity().x = 0;
		if (InputHandler::checkDown(sf::Keyboard::Left)) player->getVelocity().x = -250;
		if (InputHandler::checkUp(sf::Keyboard::Left)) player->getVelocity().x = 0;
	}

	//Aktualizuj stany
	//CHUJ DUPA CYCKI NIE PAMIETAM CO TO ROBI
	void Playing::update(float dt)
	{
		updateLevel();
		player->update(dt);
		if (player->getFlags().inAir)
		{
			Physics::applyGravity(*player, dt);
		}
		else
		{
			player->getVelocity().y = 0;
		}
		resolveCollisions();
	}


	//Rysuj obiekty UI
	void Playing::draw()
	{
		player->draw();
	}

	void Playing::resolveCollisions()
	{
		//Platforms
		for (unsigned i = 0; i < currentLevel->getPlatforms()->size(); i++)
		{
			if (Collision::collisionWithPlat(player, HitId::L, currentLevel->getPlatforms()->at(i), HitIdPlat::baseU))
			{
				if ((currentLevel->getPlatforms()->at(i).getPosition().y - player->getSize().y) - player->getPosition().y < -0.01)
				{
					player->setPosition(sf::Vector2f(
						player->getPosition().x, currentLevel->getPlatforms()->at(i).getPosition().y - player->getSize().y + 0.01
					));
				}
				player->getFlags().inAir = false;
				break;
			}
			else
			{
				player->getFlags().inAir = true;
			}
			
		}
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
