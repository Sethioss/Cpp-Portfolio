#include <iostream>
#include "board.h"

void GetTileScreenPosition(int indexPosX, int indexPosY, int ox, int oy, float& outx, float& outy)
{
	outx = ox + TILE_SIZE * indexPosX;
	outy = oy + TILE_SIZE * indexPosY;
}

void CreateTile(Tile* tile, int indexPosX, int indexPosY, int ox, int oy, Tile::Type tileType)
{
	tile->pawn = nullptr;
	tile->tuileShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	tile->position[0] = indexPosX;
	tile->position[1] = indexPosY;
	float screenX;
	float screenY;

	GetTileScreenPosition(indexPosX, indexPosY, ox, oy, screenX, screenY);
	tile->tuileShape.setPosition(screenX, screenY);

	if (tileType == Tile::Type::WALL)
	{
		tile->type = Tile::Type::WALL;
		tile->tuileShape.setFillColor(sf::Color(255, 43, 3));
	}

	else
	{
		tile->type = Tile::Type::FLOOR;
		if ((tile->position[0] + tile->position[1]) % 2 == 0)
		{
			tile->tuileShape.setFillColor(sf::Color(255, 125,16));
		}

		else
		{
			tile->tuileShape.setFillColor(sf::Color(255, 177, 3));
		}
	}

	return;
}

Board* CreateBoard(int width, int height, int ox, int oy)
{
	Board* createdBoard = new Board;

	createdBoard->size[0] = width;
	createdBoard->size[1] = height;
	createdBoard->originPosition[0] = ox;
	createdBoard->originPosition[1] = oy;

	createdBoard->Tableau = new Tile* [width];

	for (int i = 0; i < width; i++)
	{
		//Crée une nouvelle colonne
		Tile* column = new Tile[height];

		//L'assigne au nouvel emplacement
		createdBoard->Tableau[i] = column;

		for (int j = 0; j < createdBoard->size[1]; j++)
		{
			if (i == 0 || i == width-1 || j == 0 || j == height-1)
			{
				CreateTile(&(column[j]), i , j, createdBoard->originPosition[0], createdBoard->originPosition[1], Tile::Type::WALL);
			}

			else
			{
				CreateTile(&(column[j]), i, j, createdBoard->originPosition[0], createdBoard->originPosition[1], Tile::Type::FLOOR);
			}

			//std::cout << "Created tile of height " << i << " and width " << j << std::endl;
		}
	}

	return createdBoard;
}

void DisplayTile(sf::RenderWindow* window, Tile* createdTile)
{
	window->draw(createdTile->tuileShape);
	if (createdTile->pawn != nullptr)
	{
		//DisplayPawn(window, createdTile->pawn);
	}
}

void DisplayBoard(sf::RenderWindow* window, Board* createdBoard)
{
	for (int i = 0; i < createdBoard->size[0]; i++)
	{
		for (int j = 0; j < createdBoard->size[1]; j++)
		{
			DisplayTile(window, &createdBoard->Tableau[i][j]);
		}
	}
}

void DestroyBoard(Board* boardToDestroy)
{
	for (int i = 0; i < boardToDestroy->size[0]; i++)
	{
		if (boardToDestroy->Tableau[i]->pawn != nullptr)
		{
			DestroyPawn(boardToDestroy->Tableau[i]->pawn);
		}
			delete[] boardToDestroy->Tableau[i];
	}
	delete[] boardToDestroy;
}