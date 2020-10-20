#include <iostream>
#include "game.h"

const float DIFFICULTY_MIN = 1.5f;
const float DIFFICULTY_MAX = 0.7f;
const int LEVEL_DIFF_MAX = 3;

Game* CreateGame()
{
	Board* createdBoard = CreateBoard(16, 12, 0, 0);

	Game* createdGame = new Game;

	createdGame->playerDatas = nullptr;

	createdGame->playedBoard = createdBoard;
	SpawnPlayer(createdGame, createdGame->playedBoard->size[0] / 2, createdGame->playedBoard->size[1] / 2);
	SpawnEnemy(createdGame, 12, 7, 6);
	SpawnEnemy(createdGame, 12, 9, 6);

	return createdGame;
}

void DisplayGame(sf::RenderWindow* renderWindow, Game* gameToDisplay)
{
	DisplayBoard(renderWindow, gameToDisplay->playedBoard);

	std::list<Pawn*>::iterator it = gameToDisplay->pawnList.begin();

	while (it != gameToDisplay->pawnList.end())
	{
		DisplayPawn(renderWindow, (*it));
		it++;
	}
}

void UpdateGame(Game* gameToUpdate, float deltaTime)
{
	gameToUpdate->clock += deltaTime;
}

void PerformAction(Game* gameToActionOn, ACTION currentAction)
{
	std::list<Pawn*>::iterator it;
	it = gameToActionOn->pawnList.begin();

	if (gameToActionOn->theGameState == MAP)
	{
		Pawn* movePawn = new Pawn;

		if (currentAction == LEFT)
		{
			movePawn = MovePawn(gameToActionOn->playedBoard, (*it), -1, 0);
		}
		if (currentAction == RIGHT)
		{
			movePawn = MovePawn(gameToActionOn->playedBoard, (*it), 1, 0);
		}
		if (currentAction == DOWN)
		{
			movePawn = MovePawn(gameToActionOn->playedBoard, (*it), 0, 1);
		}
		if (currentAction == UP)
		{
			movePawn = MovePawn(gameToActionOn->playedBoard, (*it), 0, -1);
		}

		if (movePawn != nullptr)
		{
			SetBattleState(gameToActionOn, gameToActionOn->EnnemyDatas[movePawn->id]);
		}

	}

	else if(gameToActionOn->theGameState != MAP)
	{
		if (currentAction == SPACE)
		{
				OnBattleReceiveAction(*(gameToActionOn->currentBattle), gameToActionOn->clock);
				if (IsBattleFinished(*(gameToActionOn->currentBattle)))
				{
					std::cout << "Battle is finished, choose where you want to move next : " << std::endl;

					if (currentAction == LEFT)
					{
						MovePawn(gameToActionOn->playedBoard, (*it), -1, 0);
					}
					if (currentAction == RIGHT)
					{
						MovePawn(gameToActionOn->playedBoard, (*it), 1, 0);
					}
					if (currentAction == DOWN)
					{
						MovePawn(gameToActionOn->playedBoard, (*it), 0, 1);
					}
					if (currentAction == UP)
					{
						MovePawn(gameToActionOn->playedBoard, (*it), 0, -1);
					}

					gameToActionOn->theGameState = MAP;
					//MovePawn(gameToActionOn->playedBoard, (*it), 0, -1);
				}
		}
	}
}

void SetBattleState(Game* gameToChange, Enemy* enemyToFight)
{
	gameToChange->theGameState = BATTLE;
	gameToChange->opponent = enemyToFight;

	int roundNumber = 2;
	float difficulty = 0.0f;

	Battle createdBattle = CreateBattle();

	int levelDifference = gameToChange->opponent->level - gameToChange->playerDatas->level;

	if (levelDifference <= LEVEL_DIFF_MAX)
	{
		difficulty = DIFFICULTY_MIN;
	}
	else if (levelDifference >= LEVEL_DIFF_MAX)
	{
		difficulty = DIFFICULTY_MAX;
	}
	else
	{
		difficulty = DIFFICULTY_MIN + (DIFFICULTY_MAX - DIFFICULTY_MIN) *
			(levelDifference + LEVEL_DIFF_MAX) / (2.0f * LEVEL_DIFF_MAX);
	}

	for (int i = 0; i < gameToChange->opponent->level; i++)
	{
		if (i % 3 == 0)
		{
			roundNumber++;
		}
	}

	for (int i = 0; i < roundNumber; i++)
	{
		InitRandom();
		Round createdRound = CreateRound(GetRandomInt(1, 10), difficulty);
		AddRoundToBattle(createdRound, createdBattle);
	}

	createdBattle.roundCount = roundNumber;

	Battle* battle = new Battle;
	*battle = createdBattle;

	gameToChange->currentBattle = battle;
	StartBattle(*battle, gameToChange->clock);
}