#include "Texture_Manager.h"

Texture_Manager::Texture_Manager()
{
}

const sf::Texture & Texture_Manager::get(Texture_Name name) const
{
	return m_textures.at(name);
}

void Texture_Manager::addResource(Texture_Name name, std::string & filePath)
{

	sf::Texture tex;

	tex.loadFromFile(filePath);

	m_textures.insert(std::make_pair(name, tex));

}
