#pragma once

#include "Texture_Manager.h"
#include "Sound_Manager.h"
#include "Font_Manager.h"

struct Resource_Holder
{
private:
	Texture_Manager textures;
	Sound_Manager sounds;
	Font_Manager fonts;


public:
	static const Resource_Holder& get();

	const sf::Texture&		getTexture(Texture_Name name)	const;
	const sf::SoundBuffer&	getSound(Sound_Name name)		const;
	const sf::Font&			getFont(Font_Name name)			const;
};