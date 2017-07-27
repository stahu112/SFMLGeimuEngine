#include "Texture_Manager.h"

Texture_Manager::Texture_Manager()
{
	addResource(Texture_Name::test, "Resources/Textures/test.jpg");
	addResource(Texture_Name::slime, "Resources/Textures/Slime.png");
}
