#pragma once

#include "Game_Object.h"

class Level;
namespace State { class Playing; };
enum class LevelID;

class Character : public Game_Object
{
	
	struct baseStats
	{
		std::string ID = "Xamindar";
		unsigned BaseHP = 1;
		unsigned Level = 1;
		unsigned EXP = 0;
	};

	sf::FloatRect baseHitbox;

	baseStats baseStats;
	Level* levelHandle = nullptr;

	sf::Sprite spriteSheet;
	sf::Vector2f charSize;
	sf::Vector2f velocity = {0,0};

public:
	
	//Sets HITBOX in characters position, with or without new size
	void setBaseHitbox(sf::Vector2f size);
	void setBaseHitbox();
	//Returns baseHitbox
	sf::FloatRect getBaseHitbox() const;

	void setLevelHandle(LevelID id, State::Playing& state);
	void setVelocity(sf::Vector2f newVel);
	sf::Vector2f getVelocity() const;

	//Physics Component

	//Input Component
	virtual void handleInput() = 0;

	//State manager
	virtual void processStates() = 0;

	virtual void update(float dt);

	Character();


};

