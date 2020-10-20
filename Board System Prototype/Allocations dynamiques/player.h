#pragma once
#include <iostream>
#include "game.h"
#include "pawn.h"

struct Game;

struct Player
{
	int level = 2;
	int health = 100;
	int experiencePoints;
	int pawnId;
};

void SpawnPlayer(Game* gameToPlay, int playerTilePosX, int playerTilePosY);