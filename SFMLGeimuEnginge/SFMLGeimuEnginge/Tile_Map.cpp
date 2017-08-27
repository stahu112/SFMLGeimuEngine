#include "Tile_Map.h"
#include "Level.h"

TileMap::TileMap()
{
}

void TileMap::load(Texture_Name tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, Level lev)
{
	setLevelHandle(lev);
	levDes = tiles;

	for (unsigned i = 0; i < levelHandle->getSize().x * levelHandle->getSize().y; i++)
	{
		m_tileBoxes.emplace_back();
	}

	unsigned cyc = 0;
	unsigned bob = 0;
	unsigned i = 0;
	
	while(bob < m_tileBoxes.size())
	{
		while (cyc < levelHandle->getSize().x)
		{
			m_tileBoxes[bob].hitbox.left = cyc * 16;
			m_tileBoxes[bob].hitbox.top = i * 16;
			m_tileBoxes[bob].rect.setPosition(sf::Vector2f(cyc * 16,i*16));
			cyc++;
			bob++;
		}
		if(i < levelHandle->getSize().y) i++;
		else i = 0;
		cyc = 0;
	}

	for (unsigned i = 0; i < m_tileBoxes.size();i++)
	{
		m_tileBoxes[i].rect.setSize(sf::Vector2f(16, 16));
		if (tiles[i] == 1)
		{
			m_tileBoxes[i].tileType = TileType::Normal;
			m_tileBoxes[i].rect.setFillColor(sf::Color::Red);
		}
		else
		{
			m_tileBoxes[i].tileType = TileType::Empty;
			m_tileBoxes[i].rect.setFillColor(sf::Color::Green);
		}
	}

	m_tileset = Resource_Holder::get().getTexture(tileset);

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{

			// get the current tile number
			int tileNumber = tiles[i + j * width];

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
}

void TileMap::setLevelHandle(Level lev)
{
	levelHandle = &lev;
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_vertices, states);
}
