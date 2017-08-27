#include "Level.h"
#include "States\Playing_State.h"

//USTAW PLAYERHANDLE
void Level::setPlayerHandle(State::Playing state)
{
	PlayerHandle = state.getPlayer();
}

//ZWRACA PLAYERHANDLE
Character * Level::getPlayerHandle()
{
	return PlayerHandle;
}

//USTAW VIEW
void Level::setView()
{
	if(getPlayerHandle()) resetView();
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
	if (getPlayerHandle())
	{
		if (getPlayerHandle()->getPosition().x < 16 * 4)
		{
			levelView.reset(sf::FloatRect(0, 0, 16 * 8, 16 * 5));
		}
		else if (getPlayerHandle()->getPosition().x > (size.x - 4) * 16)
		{
			levelView.reset(sf::FloatRect((size.x * 16) - 8*16, 0, 16 * 8, 16 * 5));
		}
		else
		{
			levelView.reset(sf::FloatRect(getPlayerHandle()->getPosition().x - 16*4, getPlayerHandle()->getPosition().y, 16 * 8, 16 * 5));
		}
	}
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
	if (isAnimated) { updateAnim(); }
	Display::draw(backgroundTexture);
	Display::draw(tileMap);
}

//CONSTRUCTOR
Level::Level(
	Texture_Name TileSet,
	Texture_Name BackgroundTextureName,
	sf::Vector2u LevelSize,
	const int* LevelDesign,
	bool isAnimated,
	State::Playing & state) :
	isAnimated(isAnimated),
	size(LevelSize)
{
	setPlayerHandle(state);
	setView();
	assignBackgroundTex(BackgroundTextureName);
	tileMap.load(TileSet, tileSize, LevelDesign, LevelSize.x, LevelSize.y);
}
