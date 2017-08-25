#include "Level.h"

void Level::setView()
{
	resetView();
	Display::setView(this->levelView);
}

sf::View Level::getView() const
{
	return levelView;
}

void Level::resetView()
{
	levelView.reset(sf::FloatRect(0, 0, this->size.x*this->tileSize.x,this->size.y*this->tileSize.y));
}

void Level::assignBackgroundTex(Texture_Name name)
{
	backgroundTexture.setTexture(&Resource_Holder::get().getTexture(name));
	backgroundTexture.setSize(sf::Vector2f(sf::Vector2u(this->size.x*this->tileSize.x, this->size.y*this->tileSize.y)));
}

void Level::updateAnim()
{
	backgroundTexture.setTextureRect(backgroundAnimation.getFrame());
}

void Level::drawLevel()
{
	if (isAnimated) updateAnim();
	Display::draw(backgroundTexture);
	Display::draw(tileMap);
}

Level::Level(
	Texture_Name TileSet,
	Texture_Name BackgroundTextureName,
	sf::Vector2u LevelSize,
	const int* LevelDesign,
	bool isAnimated = false) :
	isAnimated(isAnimated),
	size(LevelSize)
{
	setView();
	assignBackgroundTex(BackgroundTextureName);
	tileMap.load(TileSet, tileSize, LevelDesign, LevelSize.x, LevelSize.y);
}
