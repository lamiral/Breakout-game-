#include "Random.h"

Random::Random()
{
	srand(time(0));
}

int Random::random(int scale)
{
	return rand() % scale;
}