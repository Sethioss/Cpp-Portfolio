#include "Round.h"
#include <iostream>

using namespace std;

Round CreateRound(float targetDuration, float difficulty)
{
	Round roundToReturn;
	
		roundToReturn.targetDuration = targetDuration;
		roundToReturn.difficulty = difficulty;
		roundToReturn.startTime = -1.0f;
		roundToReturn.endTime = -1.0f;
		roundToReturn.isVictory = false;
	

	return roundToReturn;
}

Round StartRound(Round roundToBegin, float startTime)
{
	roundToBegin.startTime = startTime;
	std::cout << "Press space in " << roundToBegin.targetDuration << " seconds! " << std::endl;

	return roundToBegin;
}

Round EndRound(Round roundToEnd, float newEndTime)
{
	roundToEnd.endTime = newEndTime;

	if (roundToEnd.endTime <= roundToEnd.targetDuration + roundToEnd.difficulty && roundToEnd.endTime >= roundToEnd.targetDuration - roundToEnd.difficulty)
	//if (roundToEnd.endTime <= roundToEnd.targetDuration + roundToEnd.difficulty && roundToEnd.endTime >= roundToEnd.targetDuration - roundToEnd.difficulty)
	{
		roundToEnd.isVictory = true;
		printf("You won! \n");
	}

	else
	{
		roundToEnd.isVictory = false;
		printf("You lost! \n");
	}
	return roundToEnd;
}