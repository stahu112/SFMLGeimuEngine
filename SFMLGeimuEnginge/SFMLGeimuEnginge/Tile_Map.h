#pragma once

#include <SFML\Graphics.hpp>
#include "Res\Resource_Holder.h"

class Level;

enum class TileType
{
	Empty,
	Normal //Platform/Ceiling
};

class TileMap : public sf::Drawable, public sf::Transformable
{	

public:

	TileMap();

	struct TileHitbox
	{
	public:
		sf::RectangleShape rect;
		sf::IntRect hitbox = {0,0,16,16};
		TileType tileType = TileType::Empty;
	};

	std::vector<TileHitbox> m_tileBoxes;

	void load(Texture_Name id, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, Level lev);

	void setLevelHandle(Level lev);

private:
	
	Level * levelHandle;

	const int* levDes;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

};
