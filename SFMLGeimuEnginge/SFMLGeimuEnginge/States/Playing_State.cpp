#include "Playing_State.h"

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
	
	void Playing::initState()
	{
		setPlayer(&Candy);
		initLevels();
		changeLevel(LevelID::level0);
		//currentLevel = &m_levels.at(LevelID::level0);
	}

	void Playing::initLevels()
	{
		Level level0(
			Texture_Name::test,
			Texture_Name::tilemap,
			"Resources/level1.txt",
			"Resources/levelCol1.txt",
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

		level1.startingPosition = { 1 * tileSize, 1 * tileSize };

		addLevel(LevelID::level0, level0);
		addLevel(LevelID::level1, level1);
	}

	//Sterowanie itp.
	void Playing::input()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player->getVelocity().y = -200; 
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player->goalVelocity.y = 200;
		
		//else player->goalVelocity.y = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player->goalVelocity.x = 200;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player->goalVelocity.x = -200;
		 
		else player->goalVelocity.x = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) changeLevel(LevelID::level1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) changeLevel(LevelID::level0);
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) currentLevel->loadTilemap("Resources / levelCol.txt");

	}

	//Aktualizuj stany
	void Playing::update(float dt)
	{
		player->update(dt);

		updateLevel(dt);

		resolveCollisions(dt);
	}


	//Rysuj obiekty UI
	void Playing::draw()
	{
		player->draw();
	}

	void Playing::resolveCollisions(float dt)
	{

		if (isDEBUG)
		{
			std::cout << "Fall: " << player->getFlags().falling << std::endl;
			std::cout << "Jump: " << player->getFlags().jumping << std::endl;
			std::cout << "VelX: " << player->getVelocity().x << " VelY: " << player->getVelocity().y << std::endl;
			std::cout << "PosX: " << player->getPosition().x << " PosY: " << player->getPosition().y << std::endl;
			std::cout << "exPosX: " << player->expPos.x << " exPosY: " << player->expPos.y << std::endl;
		}

		dt *= 1;

		if (currentLevel)
		{

			player->getSprite().setColor(sf::Color::Green);

			for (int i = 0; i < player->tiles.size(); i++)
			{
				//POD£OGA/SUFIT
				if (currentLevel->getCollisionMap()[player->tiles[i].y][player->tiles[i].x] == 1)
				{
					player->getSprite().setColor(sf::Color::Red);
					
					player->setPosition(sf::Vector2f(player->getPosition().x ,player->getPosition().y - player->getVelocity().y*dt));
					
					player->appGr = false;
					
					if (!player->getFlags().standing) player->getVelocity().y = 0;
					player->getFlags().standing = true;
					
					break;
				}
				else
				{
					player->getFlags().standing = false;
				}
				//ŒCIANY
				if (currentLevel->getCollisionMap()[player->tiles[i].y][player->tiles[i].x] == 2)
				{
					
					player->setPosition(sf::Vector2f(player->getPosition().x - player->getVelocity().x*dt, player->getPosition().y));
					player->getVelocity().x = 0;
				}

				if (currentLevel->getCollisionMap()[player->tiles[i].y][player->tiles[i].x] == 3)
				{
					
					player->setPosition(sf::Vector2f(player->getPosition().x - player->getVelocity().x*dt, player->getPosition().y));
					player->setPosition(sf::Vector2f(player->getPosition().x, player->getPosition().y - player->getVelocity().y*dt));
					player->getVelocity().x = 0;

				}

				//currentPos = currentPos + (fraction * (targetPos - currentPos))
			}

			//if (player->getPosition() < )
			//{

			//}

			if (isDEBUG)
			{
				//std::cout << currentLevel->getCollisionMap().at(1).at(0) << std::endl;
				for (int i = 0; i < currentLevel->getCollisionMap().size(); i++)
				{
					for (int j = 0; j < currentLevel->getCollisionMap()[i].size(); j++)
					{
						if (currentLevel->getCollisionMap()[i][j])
						{
							/*//player->getSprite().setColor(sf::Color::Red);
							player->setPosition(player->getPosition() - player->getVelocity()*dt);//sf::Vector2f(player->getPosition().x ,top - player->getSize().y));
							player->appGr = false;
							player->getVelocity().y = 0;
							break;*/

							float top = tileSize * i;
							float bot = (i * tileSize) + tileSize;
							float left = tileSize * j;
							float right = (j * tileSize) + tileSize;

							sf::CircleShape sh1(1), sh2(1), sh3(1), sh4(1);

							sh1.setPosition(left - 0.5, top - 0.5);
							sh2.setPosition(right - 0.5, top - 0.5);
							sh3.setPosition(left - 0.5, bot - 0.5);
							sh4.setPosition(right - 0.5, bot - 0.5);
				
							switch (currentLevel->getCollisionMap()[i][j])
							{
							case 1:
								sh1.setFillColor(sf::Color::Red);
								sh2.setFillColor(sf::Color::Red);
								sh3.setFillColor(sf::Color::Red);
								sh4.setFillColor(sf::Color::Red);
								break;

							case 2:
								sh1.setFillColor(sf::Color::Green);
								sh2.setFillColor(sf::Color::Green);
								sh3.setFillColor(sf::Color::Green);
								sh4.setFillColor(sf::Color::Green);
								break;

							case 3:
								sh1.setFillColor(sf::Color::Blue);
								sh2.setFillColor(sf::Color::Blue);
								sh3.setFillColor(sf::Color::Blue);
								sh4.setFillColor(sf::Color::Blue);
								break;
							}

							Display::draw(sh1);
							Display::draw(sh2);
							Display::draw(sh3);
							Display::draw(sh4);
						}
					}
				}
			}
		}
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
