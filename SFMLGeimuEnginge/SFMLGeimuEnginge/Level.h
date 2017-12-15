#pragma once

#include <vector>

#include "Display.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"
#include "Character.h"
#include "Box2D\Box2D.h"

constexpr float tileSize = 32;

namespace State { class Playing; };

enum class LevelID
{
	level0,
	level1
};

class Level
{
	//Size
	sf::Vector2u size;

	//tilemap
	std::vector<std::vector<sf::Vector2i>> tileMap;
	std::vector<sf::Vector2i> tempMap;


	//Background
	sf::RectangleShape backgroundTexture;
	Animation backgroundAnimation;

	sf::Sprite tile;

	bool isAnimated = false;

	std::vector<b2Body *> platforms;

	float yFactor = 16; //20;
	sf::View levelView;
	sf::Vector2f viewPort = { 20 * tileSize, 12 * tileSize };

	//PlayerHandle
	Character * playerHandle = nullptr;
	b2World * boxWorldPtr = nullptr;

public:
	
	sf::Vector2u getSize() const;
	
	b2Vec2 startingPosition = { 2,2 };
	
	b2Vec2 gravity = b2Vec2(0, 10.f);


	Character* getPlayerHandle();

	std::vector<b2Body *> & getPlatforms();

	//Background
	void assignBackgroundTex(Texture_Name name);
	void updateAnim();

	void createPlatform(float x, float y, float w, float h, b2BodyType type);
	void createRoom();



	sf::View getView() const;
	void resetView(float dt);
	void setView(float dt);


	//Draw
	void drawLevel();

	bool loadLevel(std::string path);
	void loadTileMap(Texture_Name tex, std::string path);

	Level(float width, float height, Texture_Name background, Texture_Name tileMap, bool animated, State::Playing & state);
};
