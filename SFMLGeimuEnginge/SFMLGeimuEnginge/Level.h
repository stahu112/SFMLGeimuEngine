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
	//ID n Size
	LevelID ID;
	sf::Vector2u size;

	//Background
	sf::RectangleShape backgroundTexture;
	Animation backgroundAnimation;
	bool isAnimated = false;

	std::vector<b2Body *> platforms; //"Pud³o" które jest granicami levelu

	//TEST
	sf::View levelView;

	//PlayerHandle
	Character * playerHandle = nullptr;
	b2World * boxWorldPtr = nullptr;

public:

	sf::Vector2f startingPosition = {0,0};
	b2Vec2 gravity = b2Vec2(0, 10.f);
	//PlayerHandle
	Character* getPlayerHandle();

	void createRoom();

	void createPlatform(float x, float y, float w, float h, b2BodyType type);

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

	bool loadLevel(std::string path);

	Level(float width, float height, Texture_Name background, bool animated, State::Playing & state);
};
