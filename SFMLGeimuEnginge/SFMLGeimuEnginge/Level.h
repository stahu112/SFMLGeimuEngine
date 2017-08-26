#pragma once

#include "Tile_Map.h"
#include "Display.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"
#include "LevelsDes.h"
#include "Character.h"

namespace State { class Playing; };

enum class LevelID
{
	level0
};

class Level
{
	LevelID ID;
	sf::Vector2u size;

	sf::RectangleShape backgroundTexture;
	Animation backgroundAnimation;

	bool isAnimated = false;

	sf::View levelView;

	TileMap tileMap;
	sf::Vector2u tileSize = { 16,16 };

	Character* PlayerHandle = nullptr;

public:
	//PlayerHandle
	void setPlayerHandle(State::Playing& state);
	Character* getPlayerHandle() const;

	//View
	void setView();
	sf::View getView() const;
	void resetView();

	//Background
	void assignBackgroundTex(Texture_Name name);
	void updateAnim();

	//Draw
	void drawLevel();

	Level(Texture_Name tileset, Texture_Name background, sf::Vector2u levelsize, const int* levelarray, bool animated);
};
