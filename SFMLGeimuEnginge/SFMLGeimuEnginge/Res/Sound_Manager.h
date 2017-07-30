#pragma once

#include <SFML/Audio.hpp>

#include "Resource_Manager.h"

enum class Sound_Name
{
	
};

class Sound_Manager : public Resource_Manager<Sound_Name, sf::SoundBuffer>
{

private:

public:
	Sound_Manager();
};