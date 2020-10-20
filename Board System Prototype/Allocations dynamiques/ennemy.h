#pragma once
#include <iostream>
#include "game.h"
#include "pawn.h"

struct Game;

struct Enemy
{
	int level;
	int pawnId;
};

void SpawnEnemy(Game* gameToPlay, int enemyTilePosX, int enemyTilePosY, int enemyLevel);
int KillEnemy(Game* gameToKillEnemyIn, int enemyId);