#pragma once
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include <math.h>
#include "player.h"
#include "bullet.h"
#include "display.h"

struct Player;
struct Arena;

using namespace std;

struct Game {

	Arena* arena;
	bool gameOver = false;
	string audioToPlay;
};

Game* CreateGame(sf::RenderWindow& window, int enemiesToCreate);
void UpdateGame(sf::RenderWindow& window, Game* game, float deltaTime);
void DisplayGame(Game* game, sf::RenderWindow& window);
void GetPlayerInfos(Game* game);
Game* Reload(Game* game, sf::RenderWindow& window, float deltaTime);
void DeleteGame(Game* game);
void DeleteArena(Game* game);
void DeletePlayer(Game* game); 
void PlayAudio(string audioToPlay, Game* game, sf::SoundBuffer* buffer, sf::Sound* sound);
void UpdateAudio(Game* game, sf::SoundBuffer* buffer, sf::Sound* sound);
