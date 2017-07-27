#pragma once

#include <SFML/Graphics.hpp>
#include <map>

enum class Texture_Name
{

};

class Texture_Manager
{

private:
	std::map<Texture_Name, sf::Texture> m_textures;

public:
	Texture_Manager();

	const sf::Texture& get(Texture_Name name) const;

	void addResource(Texture_Name name, std::string& filePath);

};