#include "Platform.h"



sf::FloatRect Platform::getHitbox(HitIdPlat box) const
{
	if (box == HitIdPlat::baseD) return baseD;
	if (box == HitIdPlat::baseU) return baseU;
	if (box == HitIdPlat::edgeL) return edgeL;
	if (box == HitIdPlat::edgeR) return edgeR;
}

Platform::Platform()
{
}

Platform::Platform(sf::Vector2f platPos, sf::Vector2f platSize, Texture_Name texName)
{
	size = platSize;
	Position = platPos;
	shape.setSize(platSize);
	shape.setPosition(platPos);
	shape.setTexture(&Resource_Holder::get().getTexture(texName));
	setHitboxes();
}

sf::RectangleShape Platform::getShape() const
{
	return shape;
}

void Platform::setHitboxes()
{
	edgeL.left = Position.x;
	edgeL.top = Position.y;
	edgeL.height = size.y;
	edgeL.width = step;

	edgeR.height = size.y;
	edgeR.width = step;
	edgeR.left = Position.x + size.x - step;
	edgeR.top = Position.y;

	baseU.width = size.x - (2 * step);
	baseU.height = size.y / 2;
	baseU.left = Position.x + step;
	baseU.top = Position.y;

	baseD.width = size.x - (2 * step);
	baseD.height = size.y / 2;
	baseD.left = Position.x + step;
	baseD.top = Position.y + size.y/2;
}

void Platform::changePosition(sf::Vector2f newpos)
{
	Position = newpos;
	setHitboxes();
}
