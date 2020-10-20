#pragma once
#include "Round.h"
#define ROUND_MAX 10

struct Battle
{
	Round rounds[ROUND_MAX];
	int roundCount;
	int currentRoundId;
};

Battle CreateBattle();
void AddRoundToBattle(Round roundToAdd, Battle& battleToModify);
void StartBattle(Battle& battleToModify, float battleStart);
bool IsBattleFinished(Battle& battleToEvaluate);
void OnBattleReceiveAction(Battle& battleToModify, float actionRecord);
bool isPreviousRoundVictory(Battle& battleToEvaluate);
int GetBattleVictoryCount(Battle& battleToEvaluate);