#include <fstream>
#include "Level.h"
#include "ColFilters.h"
#include "States\Playing_State.h"

void Level::createRoom()
{
	b2BodyDef floorDef;
	floorDef.position.Set(size.x/2, size.y + 0.5);
	floorDef.type = b2_staticBody;
	b2Body * floor = boxWorldPtr->CreateBody(&floorDef);

	b2PolygonShape floorShape;
	floorShape.SetAsBox(size.x/2 , 0.5);

	floor->CreateFixture(&floorShape, 0.0f);

	platforms.push_back(floor);
}

//STWORZ TILE'A
void Level::createPlatform(float x, float y, float w, float h, b2BodyType type)
{
	b2BodyDef platDef;
	platDef.position.Set(x+w/2, y+h/2);
	platDef.type = type;
	b2Body * plat = boxWorldPtr->CreateBody(&platDef);
	
	b2PolygonShape platShape;
	platShape.SetAsBox(w / 2, h/2);

	b2FixtureDef fix;
	fix.density = 1.0f;
	fix.shape = &platShape;
	fix.filter.categoryBits = ColFilters::Walls;

	plat->CreateFixture(&platShape, 1.0f);

	platforms.push_back(plat);
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

bool Level::loadLevel(std::string path)
{
	std::fstream file;

	file.open(path, std::ios::in);

	if (!file.good())
	{
		std::cout << "File not good";
		return false;
	}
	else
	{

		for (int i = 0; i < size.y; i++)
		{
			for (int j = 0; j < size.x; j++)
			{
				int val;

				file >> val;
				
				if (val) createPlatform(j, i, 1, 1, b2_staticBody);
			}
		}
	}

	file.close();

	return true;
}

Level::Level(float width, float height, Texture_Name background, bool animated, State::Playing & state) :
	isAnimated(animated)
{
	size.x = width;
	size.y = height;
	assignBackgroundTex(background);
	playerHandle = state.getPlayer();

	boxWorldPtr = state.getWorld();

	//boxWorldPtr->ShiftOrigin(b2Vec2(0, 0));

	createRoom();

	levelView.reset(sf::FloatRect(0, 0, viewPort.x, viewPort.y));

}
