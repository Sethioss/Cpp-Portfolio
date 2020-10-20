#include "board.h"
#include "pawn.h"

int nextId = 0;

Pawn* CreatePawn(int pawnPosX, int pawnPosY, Board* boardToAddOn, Pawn::state pawnState)
{
	Pawn* createdPawn = new Pawn;

	createdPawn->position[0] = -1;
	createdPawn->position[1] = -1;

	createdPawn->id = nextId;
	nextId++;

	createdPawn->visual.setRadius(TILE_SIZE / 2);

	if (pawnState == Pawn::state::PLAYER)
	{
		createdPawn->visual.setFillColor(sf::Color::White);
		createdPawn->pawnState = Pawn::state::PLAYER;
	}
	else
	{
		createdPawn->visual.setFillColor(sf::Color::Red);
		createdPawn->pawnState = Pawn::state::ENEMY;
	}


	SetPawnOnboard(createdPawn, boardToAddOn, pawnPosX, pawnPosY);

	return createdPawn;
}

void SetPawnOnboard(Pawn* pawnToSet, Board* boardToSetOn, int pawnPosX, int pawnPosY)
{
	float outputX = 0.0f;
	float outputY = 0.0f;

	GetTileScreenPosition(pawnPosX, pawnPosY, boardToSetOn->originPosition[0], boardToSetOn->originPosition[1], outputX, outputY);
	pawnToSet->position[0] = outputX;
	pawnToSet->position[1] = outputY;
	boardToSetOn->Tableau[pawnPosX][pawnPosY].pawn = pawnToSet;
	pawnToSet->visual.setPosition(outputX, outputY);
}

void DisplayPawn(sf::RenderWindow* window, Pawn* pawnToDisplay)
{
	window->draw(pawnToDisplay->visual);
}

void DestroyPawn(Pawn* pawnToDestroy)
{
	delete pawnToDestroy;
}

Pawn* MovePawn(Board* boardToMoveOn, Pawn* pawnToMove, int distanceX, int distanceY)
{
	int previousPawnPosX = pawnToMove->position[0];
	int previousPawnPosY = pawnToMove->position[1];

	int newPositionX = pawnToMove->position[0] += (distanceX * TILE_SIZE);
	int newPositionY = pawnToMove->position[1] += (distanceY * TILE_SIZE);
		
	int tableIdX = newPositionX / TILE_SIZE;
	int tableIdY = newPositionY / TILE_SIZE;

	pawnToMove->position[0] = newPositionX;
	pawnToMove->position[1] = newPositionY;

	if (newPositionX < 0 || newPositionX > (boardToMoveOn->size[0] * TILE_SIZE) - TILE_SIZE || newPositionY < 0 || newPositionY > (boardToMoveOn->size[1] * TILE_SIZE) - TILE_SIZE)
	{
		pawnToMove->position[0] = previousPawnPosX;
		pawnToMove->position[1] = previousPawnPosY;
		return nullptr;
	}

	else if (boardToMoveOn->Tableau[tableIdX][tableIdY].type == Tile::Type::WALL)
	{
		pawnToMove->position[0] = previousPawnPosX;
		pawnToMove->position[1] = previousPawnPosY;
		return nullptr;
	}
	
	else if (boardToMoveOn->Tableau[tableIdX][tableIdY].pawn != nullptr)
	{
		pawnToMove->position[0] = previousPawnPosX;
		pawnToMove->position[1] = previousPawnPosY;
		return boardToMoveOn->Tableau[tableIdX][tableIdY].pawn;
	}

	else
	{
		boardToMoveOn->Tableau[previousPawnPosX / TILE_SIZE][previousPawnPosY / TILE_SIZE].pawn = nullptr;
		SetPawnOnboard(pawnToMove, boardToMoveOn, pawnToMove->position[0] / TILE_SIZE, pawnToMove->position[1] / TILE_SIZE);
		return nullptr;
	}
}