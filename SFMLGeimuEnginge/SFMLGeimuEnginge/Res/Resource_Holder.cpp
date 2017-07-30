#include "Resource_Holder.h"

//Te metody zwracaja referencje do zasobow

//Statyczna metoda, zwraca obiekt z ktorego mozna pobrac zasoby, czytaj SINGLETON PATTERN
const Resource_Holder& Resource_Holder::get()
{
	static Resource_Holder holder;

	return holder;
}	

const sf::Texture & Resource_Holder::getTexture(Texture_Name name) const
{
	return textures.get(name);
}

const sf::SoundBuffer & Resource_Holder::getSound(Sound_Name name) const
{
	return sounds.get(name);
}

const sf::Font & Resource_Holder::getFont(Font_Name name) const
{
	return fonts.get(name);
}