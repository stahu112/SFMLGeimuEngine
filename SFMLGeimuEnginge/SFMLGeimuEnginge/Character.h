#pragma once

#include "Game_Object.h"

class Character : public Game_Object
{
	
	struct BaseStats
	{
		std::string ID = "Xamindar";
		unsigned BaseHP = 1;
		unsigned Level = 1;
		unsigned EXP = 0;
	};

	sf::FloatRect baseHitbox;

	BaseStats baseStats;

	sf::Sprite spriteSheet;
	sf::Vector2f charSize;
	sf::Vector2f velocity = {0,0};

public:
	
	//Sets HITBOX in characters position, with or without new size
	void setBaseHitbox(sf::Vector2f size);
	void setBaseHitbox();
	//Returns baseHitbox
	sf::FloatRect getBaseHitbox() const;
	
	//
	BaseStats getBaseStats() const;
	void setBaseStats(std::string ID, unsigned BaseHP, unsigned Level);

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

