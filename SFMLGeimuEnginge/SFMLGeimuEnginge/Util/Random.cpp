#include "Random.h"

void Random::init()
{
	srand(time(0));
}

int Random::intInRange(int low, int high)
{
	return rand() % (high - low +1) + low;
}

float Random::floatInRange(float low, float high)
{
	int newLow = low * 100;
	int newHigh = high * 100;


	return (float)intInRange(newLow, newHigh) / 100.f;
}
