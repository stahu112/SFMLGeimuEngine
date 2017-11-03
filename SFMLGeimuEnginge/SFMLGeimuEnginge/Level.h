#pragma once

#include <vector>
#include <fstream>
#include <cctype>
#include <string>

#include "Display.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"
#include "Character.h"

constexpr float tileSize = 32;

namespace State { class Playing; };

enum class LevelID
{
	level0,
	level1
};

class Level
{
	//ID n Size
	LevelID ID;
	sf::Vector2u size;

	//Background
	sf::RectangleShape backgroundTexture;
	Animation backgroundAnimation;
	bool isAnimated = false;

	//TEST
	sf::View levelView;

	//PlayerHandle
	Character* playerHandle = nullptr;

public:

	sf::Vector2f startingPosition = {0,0};

	//PlayerHandle
	void setPlayerHandle(State::Playing state);
	Character* getPlayerHandle();

	float yFactor = 16; //20;

	sf::Vector2f viewPort = { 20 * tileSize, 12 * tileSize };

	//GetSize
	sf::Vector2u getSize() const;

	//View
	void setView(float dt);
	sf::View getView() const;
	void resetView(float dt);

	//Background
	void assignBackgroundTex(Texture_Name name);
	void updateAnim();

	//Draw
	void drawLevel();

	Level(float width, float height, Texture_Name background, bool animated, State::Playing & state);
};
