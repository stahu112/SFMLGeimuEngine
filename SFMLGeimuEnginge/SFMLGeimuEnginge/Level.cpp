#include "Level.h"
#include "States\Playing_State.h"

//USTAW PLAYERHANDLE
void Level::setPlayerHandle(State::Playing & state)
{
	PlayerHandle = state.getPlayer();
}

//ZWRACA PLAYERHANDLE
Character * Level::getPlayerHandle() const
{
	return PlayerHandle;
}

//USTAW VIEW
void Level::setView()
{
	resetView();
	Display::setView(this->levelView);
}

//ZWRACA VIEW
sf::View Level::getView() const
{
	return levelView;
}

//RESETUJ VIEW
void Level::resetView()
{
	levelView.reset(sf::FloatRect(0, 0, this->size.x*this->tileSize.x,this->size.y*this->tileSize.y));
}

//PRZYDZIEL TLO I ZMIEN JEGO ROZMIAR TAK ZEBY OBEJMOWAL CALY POZIOM
void Level::assignBackgroundTex(Texture_Name name)
{
	backgroundTexture.setTexture(&Resource_Holder::get().getTexture(name));
	backgroundTexture.setSize(sf::Vector2f(sf::Vector2u(this->size.x*this->tileSize.x, this->size.y*this->tileSize.y)));
}

//JESLI TLO JEST ANIMOWANE
void Level::updateAnim()
{
	backgroundTexture.setTextureRect(backgroundAnimation.getFrame());
}

//DRAW
void Level::drawLevel()
{
	if (isAnimated) { updateAnim(); };
	Display::draw(backgroundTexture);
	Display::draw(tileMap);
}

//CONSTRUCTOR
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
