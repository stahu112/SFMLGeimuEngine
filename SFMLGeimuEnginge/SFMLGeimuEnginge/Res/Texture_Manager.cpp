#include "Texture_Manager.h"

Texture_Manager::Texture_Manager()
{
	//Dodaj Tekstury po ID czyli enum Texture_Name
	addResource(Texture_Name::test, "Resources/Textures/test.jpg");
	addResource(Texture_Name::test1, "Resources/Textures/test.png");
	addResource(Texture_Name::test2, "Resources/Textures/test2.jpg");
	addResource(Texture_Name::spritesheet, "Resources/Textures/spritesheet.png");
	addResource(Texture_Name::spritesheet1, "Resources/Textures/spritesheet1.png");
	addResource(Texture_Name::tilemap, "Resources/Textures/tilemap.png");

}
