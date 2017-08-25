#pragma once

#include "Game_Object.h"

class Level;
namespace State { class Playing; };
enum class LevelID;

class Character : public Game_Object
{
	
	struct baseStats
	{
		unsigned HP;
		unsigned Level;
		unsigned EXP;
	};

	baseStats baseStats;
	Level* levelHandle;

	sf::Sprite spriteSheet;
	sf::Vector2f velocity = {0,0};

public:
	
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

