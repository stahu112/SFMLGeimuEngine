#pragma once

#include "Display.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"
#include "Character.h"
#include "Platform.h"

namespace State { class Playing; };

enum class LevelID
{
	level0
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

	//Platforms
	std::vector<Platform> m_platforms;

	//PlayerHandle
	Character* PlayerHandle = nullptr;

public:
	//PlayerHandle
	void setPlayerHandle(State::Playing state);
	Character* getPlayerHandle();

	//TileSize
	sf::Vector2u tileSize = { 16, 16 };

	float yFactor = 2;

	sf::Vector2f viewPort = { 19, 10 };

	//GET PLATFORMS VECTOR
	std::vector<Platform> * getPlatforms();

	//GetSize
	sf::Vector2u getSize() const;

	//View
	void setView();
	sf::View getView() const;
	void resetView();

	//Background
	void assignBackgroundTex(Texture_Name name);
	void updateAnim();

	//Draw
	void drawLevel();

	Level(Texture_Name background, sf::Vector2u levelsize, bool animated, State::Playing & state);
};
