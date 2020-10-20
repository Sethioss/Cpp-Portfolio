#include "Battle.h"
#include <iostream>


Battle CreateBattle()
{

	//Initialiser les variables de battle

	Battle battle;

	battle.rounds[ROUND_MAX];
	battle.roundCount = 0;
	battle.currentRoundId = 0;

	return battle;
}

void AddRoundToBattle(Round roundToAdd, Battle& battleToModify)
{
		//Ajouter le round précédemment créé
		battleToModify.rounds[battleToModify.roundCount] = roundToAdd;
		battleToModify.roundCount++;
}

void StartBattle(Battle& battleToModify, float battleStart)
{
	//Débuter le combat, start le round correspondant à l'ID 0
	battleToModify.currentRoundId = 0;
	std::cout << "Bienvenue dans ce combat ! " << "Round : " << battleToModify.currentRoundId << " / " << battleToModify.roundCount << std::endl;
	StartRound(battleToModify.rounds[battleToModify.currentRoundId], battleStart);
}

bool IsBattleFinished(Battle& battleToEvaluate)
{
	//Si le roundid est supérieur ou égal au nombre de round, le combat est fini
	if (battleToEvaluate.currentRoundId >= battleToEvaluate.roundCount)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void OnBattleReceiveAction(Battle& battleToModify, float actionRecord)
{
	//End le round, et check si le combat est fini
	battleToModify.rounds[battleToModify.currentRoundId] = EndRound(battleToModify.rounds[battleToModify.currentRoundId], actionRecord);

	if (!IsBattleFinished(battleToModify))
	{
		//Passer au prochain round du combat. Vérifie si le prochain round est gagné
		battleToModify.currentRoundId++;
		StartRound(battleToModify.rounds[battleToModify.currentRoundId], actionRecord);
	}
	else 
	{
		
	}
}

int GetBattleVictoryCount(Battle& battleToEvaluate)
{
	int wins = 0;

	for (int i = 0; i <= battleToEvaluate.roundCount - 1; i++)
	{
		if (battleToEvaluate.rounds[i].isVictory == true)
		{
			wins++;
		}
	}

	return wins;
}

bool isPreviousRoundVictory(Battle& battleToEvaluate)
{
	if (battleToEvaluate.rounds[battleToEvaluate.currentRoundId - 1].isVictory == true)
	{
		return true;
	}

	else
	{
		return false;
	}
}