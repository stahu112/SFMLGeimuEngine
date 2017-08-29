#pragma once

#include "Game_Object.h"
#include "Res\Resource_Holder.h"

class Platform : public Game_Object
{

protected:
	sf::RectangleShape shape;
	sf::Vector2f size = {16, 16};

	unsigned step = 3;

public:

	sf::FloatRect edgeL;
	sf::FloatRect edgeR;
	sf::FloatRect baseU;
	sf::FloatRect baseD;

	Platform();
	Platform(sf::Vector2f platPos, sf::Vector2f platSize, Texture_Name texName);
	
	sf::RectangleShape getShape() const;

	void setHitboxes();
	void changePosition(sf::Vector2f newpos);

};

