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

std::vector<Platform> * Level::getPlatforms()
{
	return &m_platforms;
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
		if (getPlayerHandle()->getPosition().x + viewPort.x < tileSize.x * viewPort.x/2)
		{
			levelView.reset(sf::FloatRect(0, getPlayerHandle()->getPosition().y - viewPort.y/2 * tileSize.y, tileSize.x * viewPort.x, tileSize.x * viewPort.y));
		}
		else if (getPlayerHandle()->getPosition().x > (size.x - viewPort.x / 2) * tileSize.x - viewPort.x)
		{
			levelView.reset(sf::FloatRect((size.x * tileSize.x) - viewPort.x * tileSize.x, getPlayerHandle()->getPosition().y - viewPort.y / 2 * tileSize.x, tileSize.x * viewPort.x, tileSize.x * viewPort.y));
		}
		else
		{
			levelView.reset(sf::FloatRect(getPlayerHandle()->getPosition().x - tileSize.x * viewPort.x/2 + viewPort.x, getPlayerHandle()->getPosition().y - viewPort.y / 2 * tileSize.x, tileSize.x * viewPort.x, tileSize.x * viewPort.y));
		}
	}
}

//PRZYDZIEL TLO I ZMIEN JEGO ROZMIAR TAK ZEBY OBEJMOWAL CALY POZIOM
void Level::assignBackgroundTex(Texture_Name name)
{
	backgroundTexture.setTexture(&Resource_Holder::get().getTexture(name));
	backgroundTexture.setSize(sf::Vector2f(sf::Vector2u(size.x * tileSize.x, size.y * tileSize.x)));
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

	for (unsigned i = 0; i < m_platforms.size(); i++)
	{
		Display::draw(m_platforms[i].getShape());
	}
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
