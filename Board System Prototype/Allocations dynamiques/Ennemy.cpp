#include "ennemy.h"

void SpawnEnemy(Game* gameToPlay, int enemyTilePosX, int enemyTilePosY, int enemyLevel)
{
	Enemy* createdEnemy = new Enemy;

	createdEnemy->level = enemyLevel;
	Pawn* linkedPawn = CreatePawn(enemyTilePosX, enemyTilePosY, gameToPlay->playedBoard, Pawn::state::ENEMY);
	
	createdEnemy->pawnId = linkedPawn->id;
	gameToPlay->pawnList.push_back(linkedPawn);
	gameToPlay->EnnemyDatas[createdEnemy->pawnId] = createdEnemy;
}

int KillEnemy(Game* gameToKillEnemyIn, int enemyId)
{
	std::list<Pawn*>::iterator it = gameToKillEnemyIn->pawnList.begin();

	gameToKillEnemyIn->playedBoard->Tableau[(*it)->position[0]][(*it)->position[1]].pawn = nullptr;
	DestroyPawn((*it));
	it = gameToKillEnemyIn->pawnList.erase(it);

	std::map<int, Enemy*>::iterator itDic = gameToKillEnemyIn->EnnemyDatas.find(enemyId);
	gameToKillEnemyIn->EnnemyDatas.erase(itDic);

	return 50;
}