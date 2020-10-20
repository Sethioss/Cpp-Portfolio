#include "player.h"

void SpawnPlayer(Game* gameToPlay, int playerTilePosX, int playerTilePosY)
{
	Player* player = new Player;

	player->experiencePoints = 0;
	player->health = 100;
	Pawn* createdPawn = CreatePawn(playerTilePosX, playerTilePosY, gameToPlay->playedBoard, Pawn::state::PLAYER);
	player->pawnId = createdPawn->id;
	gameToPlay->pawnList.push_back(createdPawn);
	gameToPlay->playerDatas = player;
}