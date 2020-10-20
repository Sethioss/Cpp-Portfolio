#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"

struct Board;

struct Pawn {

	int position[2];
	enum state {
		ENEMY,
		PLAYER
	};

	state pawnState;
	int id;
	sf::CircleShape visual;
};

Pawn* CreatePawn(int pawnPosX, int pawnPosY, Board* boardToAddOn, Pawn::state pawnState);
void SetPawnOnboard(Pawn* pawnToSet, Board* boardToSetOn, int pawnPosX, int pawnPosY);
void DisplayPawn(sf::RenderWindow* window, Pawn* pawnToDisplay);
void DestroyPawn(Pawn* pawnToDestroy);
Pawn* MovePawn(Board* boardToMoveOn, Pawn* pawnToMove, int distanceX, int distanceY);