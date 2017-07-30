//To jest na razie nie uzywane ale zrobilem generator liczb losowych z wybranego przedzialu
//Wiadomo do gier sie przydaje

#include "Random.h"

//Inicjuj seeda na podstawie czasu systemowego
void Random::init()
{
	gen.seed(std::time(nullptr));
}

//Losuj liczbe calkowita z przedzialu od 'low' do 'high'
int Random::intInRange(int low, int high)
{
	std::uniform_int_distribution<int> dist(low, high);
	return dist(gen);
}

//Losuj liczbe zmiennoprzecinkowa z przedzialu od 'low' do 'high'
float Random::floatInRange(float low, float high)
{
	std::uniform_real_distribution<float> dist(low, high);
	return dist(gen);
}

//TODO Generator z rozkladem normalnym