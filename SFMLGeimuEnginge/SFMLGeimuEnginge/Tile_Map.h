#pragma once

#include <SFML\Graphics.hpp>
#include "Res\Resource_Holder.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	void load(Texture_Name id, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

};

