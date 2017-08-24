#pragma once

#include "Game_Object.h"
#include "Animation.h"

class Level;

class Character : public Game_Object
{
	
	enum class State
	{
		Idle,
		WalkRight,
		WalkLeft,
		Jumping
	};

	enum class AnimationID
	{

	};

	State currentState;

	Level* levelHandle;

	sf::Sprite sprite;
	sf::Vector2f velocity = {0,0};

	//Animation Component
	std::map<AnimationID, Animation> m_animations;

public:
	void setAnimations();
	sf::IntRect getFrame(AnimationID id);
	
	//Physics Component
	void applyPhysics(float dt);

	//Input Component
	void handleInput();

	//State manager
	void processStates();

	void update(float dt) override;

	Character();


};

