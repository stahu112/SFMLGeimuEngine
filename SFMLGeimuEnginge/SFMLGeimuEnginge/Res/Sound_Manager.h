#pragma once

#include <SFML/Audio.hpp>

#include <map>

enum class Sound_Name
{

};

class Sound_Manager
{

	const sf::SoundBuffer& get(Sound_Name name) const;

private:
	std::map<Sound_Name, sf::SoundBuffer> m_sounds;

	void addResource(Sound_Name name, std::string& filePath);

public:

};