#pragma once

#include "Tile_Map.h"
#include "Display.h"
#include "Res\Resource_Holder.h"

enum class LevelID
{
	level0
};

class Level
{
	LevelID ID;
	sf::Vector2f size;



	std::vector<sf::RectangleShape> m_backgroundLayers;
	bool assignBackground(std::string& path);


	TileMap tileMap;

public:
	void drawLevel();

	Level();
};

