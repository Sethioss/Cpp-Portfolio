#pragma once
#include <SFML/Graphics.hpp>
#include "pawn.h"

struct Board;

#define TILE_SIZE 50

struct Tile {
	int position[2];

	enum Type {
			WALL,
			FLOOR
	};

	Type type;
	Pawn* pawn;
	sf::RectangleShape tuileShape;
};

struct Board {

	int size[2];
	int originPosition[2];
	Tile** Tableau;
};

void GetTileScreenPosition(int indexPosX, int indexPosY, int ox, int oy, float& outx, float& outy);
void CreateTile(Tile* tile, int indexPosX, int indexPosY, int ox, int oy, Tile::Type tileType);
Board* CreateBoard(int width, int height, int ox, int oy);
void DisplayTile(sf::RenderWindow* window, Tile* createdTile);
void DisplayBoard(sf::RenderWindow* window, Board* createdBoard);
void DestroyBoard(Board* boardToDestroy);