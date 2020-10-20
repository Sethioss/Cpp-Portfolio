#pragma once
#include <list>
#include "board.h"
#include "player.h"
#include "ennemy.h"
#include "pawn.h"
#include "Round.h"
#include "Battle.h"
#include <map>
#include "ChronoSpacerUtils.h"

struct Player;
struct Enemy;
struct Board;
struct Pawn;

enum GAME_STATE
{
	MAP,
	BATTLE
};

struct Game
{
	Board* playedBoard;
	Player* playerDatas;
	std::map<int, Enemy*> EnnemyDatas;
	std::list<Pawn*> pawnList;
	GAME_STATE theGameState = MAP;
	Battle* currentBattle = nullptr;
	Enemy* opponent = nullptr;
	float clock = 0.0f;
};

enum ACTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE
};

Game* CreateGame();
void DisplayGame(sf::RenderWindow* renderWindow, Game* gameToDisplay);
void UpdateGame(Game* gameToUpdate, float deltaTime);
void PerformAction(Game* gameToActionOn, ACTION currentAction);
void SetBattleState(Game* gameToChange, Enemy* enemyToFight);