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
	dt *= 6;

	// IF FALLING
	//if (!playerHandle->getFlags().inAir) yFactor = 25;
	//else yFactor = 0;

	if (playerHandle)
	{
		if (playerHandle->getPosition().x + playerHandle->getSize().x/2 - levelView.getSize().x / 2 <= 0)
		{
			levelView.setCenter(levelView.getSize().x/2 , levelView.getCenter().y + (dt * (playerHandle->getPosition().y - levelView.getCenter().y + playerHandle->getSize().y / 2 - yFactor)));
		}
		else if (playerHandle->getPosition().x + playerHandle->getSize().x / 2 + levelView.getSize().x / 2 >= size.x * tileSize)
		{
			levelView.setCenter(size.x * tileSize - levelView.getSize().x / 2, levelView.getCenter().y + (dt * (playerHandle->getPosition().y - levelView.getCenter().y + playerHandle->getSize().y / 2 - yFactor)));
		}
		else
		//currentPos = currentPos + (fraction * (targetPos - currentPos))
		levelView.setCenter(playerHandle->getPosition().x + playerHandle->getSize().x / 2, levelView.getCenter().y + (dt * (playerHandle->getPosition().y - levelView.getCenter().y + playerHandle->getSize().y / 2 - yFactor)));
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

void Level::loadTilemap(const std::string & path)
{

	tempMap.clear();
	tileMap.clear();

	std::ifstream openFile(path);
	if (openFile.is_open())
	{
		while (!openFile.eof())
		{
			std::string str;
			openFile >> str;
			char x = str[0], y = str[2];
			if (!isdigit(x) || !isdigit(y))
				tempMap.push_back(sf::Vector2i(-1, -1));
			else
				tempMap.push_back(sf::Vector2i(x - '0', y - '0'));

			if (openFile.peek() == '\n')
			{
				tileMap.push_back(tempMap);
				tempMap.clear();
			}
		}
		tileMap.push_back(tempMap);
	}
}

//DRAW
void Level::drawLevel()
{
	if (isAnimated) { updateAnim(); }
	Display::draw(backgroundTexture);

	for (int i = 0; i < tileMap.size(); i++)
	{
		for (int j = 0; j < tileMap[i].size(); j++)
		{
			if (tileMap[i][j].x != -1 && tileMap[i][j].y != -1)
			{
				tile.setPosition(j * tileSize, i * tileSize);
				tile.setTextureRect(sf::IntRect(tileMap[i][j].x * tileSize, tileMap[i][j].y * tileSize, tileSize, tileSize));
				Display::draw(tile);
			}
		}
	}
}

//CONSTRUCTOR
Level::Level(
	Texture_Name BackgroundTextureName,
	Texture_Name TileSet,
	const std::string & LevelPath,
	sf::Vector2u LevelSize,
	bool isAnimated,
	State::Playing & state) :
	isAnimated(isAnimated),
	size(LevelSize)
{
	tile.setTexture(Resource_Holder::get().getTexture(TileSet));
	setPlayerHandle(state);
	assignBackgroundTex(BackgroundTextureName);
	loadTilemap(LevelPath);
	levelView.reset(sf::FloatRect(0, 0, viewPort.x, viewPort.y));
}
