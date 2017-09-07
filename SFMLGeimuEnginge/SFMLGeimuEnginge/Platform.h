#pragma once

#include "Game_Object.h"
#include "Res\Resource_Holder.h"

enum class HitIdPlat
{
	edgeL,
	edgeR,
	baseU,
	baseD
};

class Platform : public Game_Object
{

protected:

public:

	sf::FloatRect getHitbox(HitIdPlat box) const;

	Platform();
	Platform(sf::Vector2f platPos, sf::Vector2f platSize, Texture_Name texName);
	
	sf::RectangleShape getShape() const;

	void setHitboxes();
	void changePosition