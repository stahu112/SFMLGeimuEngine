#pragma once

#include "Tile_Map.h"
#include "Display.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"


const int level0des[] = {
	0,0,0,0,0,0,0,0,0,0,
	2,4,1,0,0,0,0,0,0,0,
	0,4,4,4,4,4,4,4,4,0,
	0,4,4,4,4,4,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
};

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

public:

	void setView();
	sf::View getView() const;

	void resetView();

	void assignBackgroundTex(Texture_Name name);

	void updateAnim();

	void drawLevel();

	Level(Texture_Name tileset, Texture_Name background, sf::Vector2u levelsize, const int* levelarray, bool animated);
};
