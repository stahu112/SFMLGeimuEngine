#include "Level.h"

bool Level::assignBackground(std::string & path)
{
	return false;
}

void Level::drawLevel()
{
	for (unsigned i = 0; i < m_backgroundLayers.size(); i++)
	{
		Display::draw(m_backgroundLayers.at(i));
	}

	Display::draw(tileMap);
}

Level::Level()
{
}
