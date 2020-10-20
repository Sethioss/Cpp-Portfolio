#include "game.h"
#include "utility.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// --- Initialise tout le jeu --- // 
Game* CreateGame(sf::RenderWindow& window, int enemiesToCreate)
{
	Game* createdGame = new Game();

	Player* createdPlayer = CreatePlayer("Roger", 100, 270);
	Arena* createdArena = CreateArena(createdPlayer, window);

	createdGame->arena = createdArena;

	return createdGame;
}

// --- Met à jour tous les paramètres du jeu --- // 
void UpdateGame(sf::RenderWindow& window, Game* game, float deltaTime)
{
	if (game->arena->player->health > 0)
	{
		CheckCollisions(game->arena, game->arena->player, window, deltaTime, game);

		srand(time(NULL));
		UpdatePlayer(game->arena->player, game->arena, window, deltaTime, game);
		UpdateEnemy(game->arena, window, deltaTime);
		UpdateBullet(game->arena->player->currentWeapon, game->arena, window, deltaTime);
	}
}

// --- Affiche les éléments du jeu --- //(
void DisplayGame(Game* game, sf::RenderWindow& window)
{
	DisplayPlayer(game->arena, window);
	DisplayPlayerLife(game->arena, window);
	DisplayArena(game->arena, window);
	DisplayEnemies(game->arena, window);
	DisplayBullet(game->arena, window);
	DisplayWeaponInfo(game->arena, window);
	DisplayWeapons(game->arena, window);
	DisplayWave(game->arena, window);

	if (game->arena->player->health <= 0)
	{
		DisplayLoose(game->arena, window, game);
	}

	if (game->arena->currentWave > 5 && game->arena->enemyList.size() == 0)
	{
		DisplayWin(game->arena, window, game);
	}
}

// --- Affiche les informations du joueur --- //
void GetPlayerInfos(Game* game)
{
	DisplayInfo(game->arena->player);
	game->arena->player->currentWeapon->WeaponDesc(game->arena->player->currentWeapon->name, game->arena->player->currentWeapon->maxAmmo, game->arena->player->currentWeapon->damage,
		game->arena->player->currentWeapon->cadency, game->arena->player->currentWeapon->knockBackSpeed);
}

// --- Supprime la game et Reload une nouvelle --- //
Game* Reload(Game* game, sf::RenderWindow& window, float deltaTime)
{
	DeleteGame(game);
	game = CreateGame(window, 0);
	game->gameOver = false;

	return game;
}

void DeleteGame(Game* game)
{
	DeletePlayer(game);
	DeleteArena(game);
	delete game;
}

void DeletePlayer(Game* game)
{
	delete game->arena->player;
}

void DeleteArena(Game* game)
{
	for (int i = 0; i < game->arena->enemyList.size(); i++)
	{
		delete game->arena->enemyList[i];
	}

	for (int i = 0; i < game->arena->bulletList.size(); i++)
	{
		delete game->arena->bulletList[i];
	}

	for (int i = 0; i < game->arena->newWeaponList.size(); i++)
	{
		delete game->arena->newWeaponList[i];
	}

	delete game->arena;
}

void UpdateAudio(Game* game, sf::SoundBuffer* buffer, sf::Sound* sound)
{
	PlayAudio(game->audioToPlay, game, buffer, sound);
}

void PlayAudio(string audioToPlay, Game* game, sf::SoundBuffer* buffer, sf::Sound* sound)
{

	if (game->audioToPlay != "")
	{
		if (!(*buffer).loadFromFile(audioToPlay))
		{
			cout << "ERROR" << endl;
		}

		(*sound).setBuffer(*buffer);
		(*sound).setVolume(25.f);
		(*sound).play();

		game->audioToPlay = "";
	}
}