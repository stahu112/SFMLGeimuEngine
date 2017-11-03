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
	dt *= 3;

	// IF FALLING
	//if (!playerHandle->getFlags().inAir) yFactor = 25;
	//else yFactor = 0;

	//levelView.getCenter().x + (dt * (playerHandle->getPosition().x + playerHandle->getSize().x/2 - levelView.getCenter().x))

	if (playerHandle)
	{
		if (size.x * tileSize >= viewPort.x)
		{
			if (playerHandle->getPosition().x + playerHandle->getSize().x / 2 - levelView.getSize().x / 2 <= 0)
			{
				levelView.setCenter(levelView.getCenter().x + (dt * (levelView.getSize().x / 2 - levelView.getCenter().x) ),
					levelView.getCenter().y + (dt * (playerHandle->getPosition().y - levelView.getCenter().y + playerHandle->getSize().y / 2 - yFactor)));
			}
			else if (playerHandle->getPosition().x + playerHandle->getSize().x / 2 + levelView.getSize().x / 2 >= size.x * tileSize)
			{
				levelView.setCenter(levelView.getCenter().x + ( dt * (size.x * tileSize - levelView.getSize().x / 2 - levelView.getCenter().x) ),
					levelView.getCenter().y + (dt * (playerHandle->getPosition().y - levelView.getCenter().y + playerHandle->getSize().y / 2 - yFactor)));
			}
			else
				//currentPos = currentPos + (fraction * (targetPos - currentPos))
				levelView.setCenter(levelView.getCenter().x + (dt * (playerHandle->getPosition().x + playerHandle->getSize().x/2 - levelView.getCenter().x)),
					levelView.getCenter().y + (dt * (playerHandle->getPosition().y - levelView.getCenter().y + playerHandle->getSize().y / 2 - yFactor)));
		}
		else
		{
			levelView.setCenter(size.x/2 * tileSize, size.y/2 * tileSize);
		}
	}
}

//PRZYDZIEL TLO I ZMIEN JEGO ROZMIAR TAK ZEBY OBEJMOWAL CALY POZIOM
void Level::assignBackgroundTex(Texture_Name name)
{
	backgroundTexture.setTexture(&Resource_Holder::get().getTexture(name));
	backgroundTexture.setSize(sf::Vector2f(size.x * tileSize, size.y * tileSize));
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

Level::Level(float width, float height, Texture_Name background, bool animated, State::Playing & state) :
	isAnimated(animated)
{
	size.x = width;
	size.y = height;
	assignBackgroundTex(background);
	setPlayerHandle(state);
	levelView.reset(sf::FloatRect(0, 0, viewPort.x, viewPort.y));
}
