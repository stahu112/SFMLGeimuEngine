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
			Texture_Name::test2,
			Texture_Name::tilemap,
			"Resources/level.txt",
			"Resources/levelCol.txt",
			false,
			*this
		);

		Level level1(
			Texture_Name::test,
			Texture_Name::tilemap,
			"Resources/level.txt",
			"Resources/levelCol.txt",
			false,
			*this
		);

		addLevel(LevelID::level0, level0);
		addLevel(LevelID::level1, level1);
	}

	//Sterowanie itp.
	void Playing::input()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player->getFlags().inAir)
		{
			player->getFlags().inAir = true;
			player->getVelocity().y = -300;
		}

		if (InputHandler::checkDown(sf::Keyboard::L)) currentLevel->loadTilemap("Resources/level.txt");

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player->goalVelocity.x = 200;
		if (InputHandler::checkUp(sf::Keyboard::D)) player->goalVelocity.x = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player->goalVelocity.x = -200;
		if (InputHandler::checkUp(sf::Keyboard::A)) player->goalVelocity.x = 0;

		if (InputHandler::checkDown(sf::Keyboard::O)) changeLevel(LevelID::level1);

		if (InputHandler::checkDown(sf::Keyboard::Up)) player->getVelocity().y = -100;
		if (InputHandler::checkDown(sf::Keyboard::Down)) player->getVelocity().y = 100;
		if (InputHandler::checkDown(sf::Keyboard::Left)) player->getVelocity().x = -100;
		if (InputHandler::checkDown(sf::Keyboard::Right)) player->getVelocity().x = 100;
		if (InputHandler::checkUp(sf::Keyboard::Up)) player->getVelocity().y = 0;
		if (InputHandler::checkUp(sf::Keyboard::Down)) player->getVelocity().y = 0;
		if (InputHandler::checkUp(sf::Keyboard::Left)) player->getVelocity().x = 0;
		if (InputHandler::checkUp(sf::Keyboard::Right)) player->getVelocity().x = 0;

	}

	//Aktualizuj stany
	void Playing::update(float dt)
	{
		updateLevel(dt);

		player->getVelocity().x = Physics::approach(player->goalVelocity.x, player->getVelocity().x, dt);

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
		player->getSprite().setColor(sf::Color::Green);
		//DZIA£A KURWAAA HAHAHA
		for (unsigned i = 0; i < currentLevel->getCollisionMap().size(); i++)
		{
			for (unsigned j = 0; j < currentLevel->getCollisionMap()[i].size(); j++)
			{
				if (currentLevel->getCollisionMap()[i][j])
				{
					int bot, top, left, right;
					bot = i * tileSize + tileSize;
					top = i * tileSize;
					left = j * tileSize;
					right = j * tileSize + tileSize;

					if (player->right < left || player->left > right
						|| player->top > bot || player->bot < top)
					{
						//NoCollision
					}
					else
					{
						//Collision
						player->getSprite().setColor(sf::Color::Red);
						break;
					}
				}
			}
		}
		
		//Stay on ground
		if (player->getPosition().y >= currentLevel->getSize().y * tileSize - player->getSize().y)
		{
			player->getFlags().inAir = false;
			player->setPosition(sf::Vector2f(player->getPosition().x, currentLevel->getSize().y * tileSize - player->getSize().y));
		}
		else
			player->getFlags().inAir = true;
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
