#pragma once
#include "ChronoSpacerUtils.h"

struct Round {

	float targetDuration;
	float difficulty;
	float startTime;
	float endTime;
	bool isVictory;

};

Round CreateRound(float targetDuration, float difficulty);
Round StartRound(Round roundToBegin, float startTime);
Round EndRound(Round roundToEnd, float endTime);
