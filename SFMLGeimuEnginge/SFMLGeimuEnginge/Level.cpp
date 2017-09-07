#include "Level.h"
#include "States\Playing_State.h"

//USTAW PLAYERHANDLE
void Level::setPlayerHandle(State::Playing state)
{
	playerHandle = state.getPlayer();
}

//ZWRACA PLAYERHANDLE
Character * Level::getPlayerHandle()
{
	return playerHandle;
}

sf::Vector2u Level::getSize() const
{
	return size;
}

//USTAW VIEW
void Level::setView(float dt)
{
	if(playerHandle) resetView(dt);
	Display::setView(this->levelView);
}

//ZWRACA VIEW
sf::View Level::getView() const
{
	return levelView;
}

//RESETUJ VIEW
void Level::resetView(float dt)
{
	dt *= 9;

	if (playerHandle)
	{
		if (playerHandle->getPosition().x + playerHandle->getSize().x/2 - levelView.getSize().x / 2 <= 0)
		{
			levelView.setCenter(levelView.getSize().x/2 ,
				levelView.getCenter().y + (dt * (playerHandle->getPosition().y - levelView.getCenter().y + playerHandle->getSize().y / 2 - yFactor)));
		}
		else if (playerHandle->getPosition().x + playerHandle->getSize().x / 2 + levelView.getSize().x / 2 >= size.x * tileSize)
		{
			levelView.setCenter(size.x * tileSize - levelView.getSize().x / 2,
				levelView.getCenter().y + (dt * (playerHandle->getPosition().y - levelView.getCenter().y + playerHandle->getSize().y / 2 - yFactor)));
		}
		else
		//currentPos = currentPos + (fraction * (targetPos - currentPos))
		levelView.setCenter(playerHandle->getPosition().x + playerHandle->getSize().x / 2,
			levelView.getCenter().y + (dt * (playerHandle->getPosition().y - levelView.getCenter().y + playerHandle->getSize().y / 2 - yFactor)));
	}
}

//PRZYDZIEL TLO I ZMIEN JEGO ROZMIAR TAK ZEBY OBEJMOWAL CALY POZIOM
void Level::assignBackgroundTex(Texture_Name name)
{
	backgroundTexture.setTexture(&Resource_Holder::get().getTexture(name));
	backgroundTexture.setSize(sf::Vector2f(sf::Vector2u(size.x * tileSize, size.y * tileSize)));
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
	levelView.reset(sf::FloatRect(0, 0, viewPort.x, viewPort.y));
}
