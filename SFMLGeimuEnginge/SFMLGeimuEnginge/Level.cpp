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

std::vector<std::vector<int>> Level::getCollisionMap() const
{
	return collisionMap;
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

void Level::loadTilemap(const std::string & path)
{
	std::vector<sf::Vector2i> tempMap;
	tileMap.clear();

	std::ifstream openFile(path);
	if (openFile.is_open())
	{
		std::string sizeStrX, sizeStrY;
		openFile >> sizeStrX;
		openFile >> sizeStrY;

		size = sf::Vector2u(std::stoi(sizeStrX), std::stoi(sizeStrY));

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

void Level::loadCollisionmap(const std::string & path)
{
	std::vector<int> tempMap;
	tempMap.clear();
	collisionMap.clear();

	std::ifstream openFile(path);
	if (openFile.is_open())
	{
		while (!openFile.eof())
		{
			std::string str;
			openFile >> str;
			int value = std::stoi(str);
			if (value)
				tempMap.push_back(value);
			else
				tempMap.push_back(0);

			if (openFile.peek() == '\n')
			{
				collisionMap.push_back(tempMap);
				tempMap.clear();
			}
		}
		collisionMap.push_back(tempMap);
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
	const std::string & LevelCol,
	bool isAnimated,
	State::Playing & state) :
	isAnimated(isAnimated)
{
	tile.setTexture(Resource_Holder::get().getTexture(TileSet));
	setPlayerHandle(state);
	loadTilemap(LevelPath);
	loadCollisionmap(LevelCol);
	levelView.reset(sf::FloatRect(0, 0, viewPort.x, viewPort.y));
	assignBackgroundTex(BackgroundTextureName);
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
