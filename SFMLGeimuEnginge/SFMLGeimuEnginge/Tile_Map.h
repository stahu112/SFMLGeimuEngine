#pragma once

#include <SFML\Graphics.hpp>
#include "Res\Resource_Holder.h"

enum class TileType
{
	Floor, //Basic ground
	Normal, //Platform/Ceiling
	Wall //Wall
};

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	void load(Texture_Name id, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	struct TileHitbox
	{
		sf::IntRect hitbox = { 0,0,16,16 };
		TileType tileType = TileType::Normal;
	};

};
