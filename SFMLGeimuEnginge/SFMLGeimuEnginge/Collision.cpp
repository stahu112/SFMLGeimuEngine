#include "Collision.h"

#include "Character.h"
#include "Platform.h"

bool Collision::collisionWithPlat(Character * chara, HitId box, Platform plat, HitIdPlat platbox)
{
	if (chara->getHitbox(box).intersects(
		plat.getHitbox(platbox)
	)) return true;
	else return false;
}

Collision::Collision()
{
}
