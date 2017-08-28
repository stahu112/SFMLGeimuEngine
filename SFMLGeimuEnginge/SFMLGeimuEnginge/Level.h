#pragma once

#include "Display.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"
#include "Character.h"

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

	//PlayerHandle
	Character* PlayerHandle = nullptr;

public:
	//PlayerHandle
	void setPlayerHandle(State::Playing state);
	Character* getPlayerHandle();

	sf::Vector2u tileSize = { 16, 16 };

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
