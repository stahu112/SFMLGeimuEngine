#pragma once

class Character;
class Platform;

enum class HitId;
enum class HitIdPlat;

class Collision
{
public:

	static bool collisionWithPlat(Character * chara, HitId box, Platform plat, HitIdPlat platbox);

	Collision();
};

