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

		for (unsigned i = 0; i < getCurrentLevel()->getTileMap().m_tileBoxes.size(); i++)
		{
			//Display::draw(getCurrentLevel()->getTileMap().m_tileBoxes[i].rect);

			if (getPlayer()->getBaseHitbox().intersects(
				getCurrentLevel()->getTileMap().m_tileBoxes[i].hitbox) &&
				getCurrentLevel()->getTileMap().m_tileBoxes[i].tileType == TileType::Normal)
			{
				getPlayer()->getFlags().onGround = true;
			}
			else if (getPlayer()->getBaseHitbox().intersects(
				getCurrentLevel()->getTileMap().m_tileBoxes[i].hitbox) &&
				getCurrentLevel()->getTileMap().m_tileBoxes[i].tileType == TileType::Empty)
			{
				getPlayer()->getFlags().onGround = false;
			}
		}
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
			//Display::draw(currentLevel->getTileMap().m_tileBoxes[1].rect);
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
			sf::Vector2u(10,10),
			level0des,
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
