#include "ChronoSpacerUtils.h"
#include <cstdlib>
#include <ctime>

void InitRandom()
{
	srand(time(NULL));
}

int GetRandomInt(int minimalBorn, int maximalBorn)
{
	int randomNumber = minimalBorn + rand() % (maximalBorn - minimalBorn);
	return randomNumber;
}