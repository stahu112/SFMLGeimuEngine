#pragma once

#include <SFML/Graphics.hpp>

#include <map>

enum class Font_Name
{

};

class Font_Manager
{

private:
	std::map < Font_Name, sf::Font > m_fonts;

	void addResource(Font_Name name, std::string& filePath);

public:

	const sf::Font& get(Font_Name name);
};