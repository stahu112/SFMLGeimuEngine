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

sf::Vector2u Level::getSize() const
{
	return size;
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
		//levelView.reset(sf::FloatRect(0, 0, Display::screenSize.x, Display::screenSize.y));
		if (getPlayerHandle()->getPosition().x + 8 < (float)tileSize.x * 4)
		{
			levelView.reset(sf::FloatRect(0, getPlayerHandle()->getPosition().y - 2*16, (float)tileSize.x * 8, (float)tileSize.x * 6));
		}
		else if (getPlayerHandle()->getPosition().x > (size.x - 4) * (float)tileSize.x -8)
		{
			levelView.reset(sf::FloatRect((size.x * (float)tileSize.x) - 8* (float)tileSize.x, getPlayerHandle()->getPosition().y - 2*16, (float)tileSize.x * 8, (float)tileSize.x * 6));
		}
		else
		{
			levelView.reset(sf::FloatRect(getPlayerHandle()->getPosition().x - (float)tileSize.x *4+8, getPlayerHandle()->getPosition().y - 2*16, (float)tileSize.x * 8, (float)tileSize.x * 6));
		}
	}
}

//PRZYDZIEL TLO I ZMIEN JEGO ROZMIAR TAK ZEBY OBEJMOWAL CALY POZIOM
void Level::assignBackgroundTex(Texture_Name name)
{
	backgroundTexture.setTexture(&Resource_Holder::get().getTexture(name));
	backgroundTexture.setSize(sf::Vector2f(sf::Vector2u(this->size.x*this->tileSize.x, this->size.y*this->tileSize.x)));
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
}

//CONSTRUCTOR
Level::Level(
	Texture_Name BackgroundTextureName,
	sf::Vector2u LevelSize,
	bool isAnimated,
	State::Playing & state) :
	isAnimated(isAnimated),
	size(LevelSize)
{
	setPlayerHandle(state);
	assignBackgroundTex(BackgroundTextureName);
	setView();
}
