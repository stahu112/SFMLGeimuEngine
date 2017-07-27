#include "Sound_Manager.h"

const sf::SoundBuffer & Sound_Manager::get(Sound_Name name) const
{
	return m_sounds.at(name);
}

void Sound_Manager::addResource(Sound_Name name, std::string & filePath)
{
	sf::SoundBuffer sbuffer;

	sbuffer.loadFromFile(filePath);

	m_sounds.insert(std::make_pair(name, sbuffer));
}
