#include "Font_Manager.h"

void Font_Manager::addResource(Font_Name name, std::string & filePath)
{
	sf::Font font;
	font.loadFromFile(filePath);

	m_fonts.insert(std::make_pair(name, font));
}

const sf::Font & Font_Manager::get(Font_Name name)
{
	return m_fonts.at(name);
}
