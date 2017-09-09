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

	sf::Sprite tile;

	std::vector<sf::Vector2i> tempMap;
	std::vector<std::vector<sf::Vector2i>> tileMap;

	//TEST
	sf::View levelView;

	//PlayerHandle
	Character* playerHandle = nullptr;

public:

	sf::Vector2f startingPosition = {0, 0};

	//PlayerHandle
	void setPlayerHandle(State::Playing state);
	Character* getPlayerHandle();

	float yFactor = 16; //20;

	sf::Vector2f viewPort = { 20 * tileSize, 15 * tileSize };

	//GetSize
	sf::Vector2u getSize() const;

	//View
	void setView(float dt);
	sf::View getView() const;
	void resetView(float dt);

	//Background
	void assignBackgroundTex(Texture_Name name);
	void updateAnim();

	//Setup Tilemap
	void loadTilemap(const std::string & path);

	//Draw
	void drawLevel();

	Level(Texture_Name background, Texture_Name tileSet, const std::string & LevelPath, bool animated, State::Playing & state);
};
