#pragma once
#include <SFML/Graphics.hpp>
#include "arena.h"
#include "game.h"
struct Game;
struct Arena;

void DisplayPlayer(Arena* arena, sf::RenderWindow& window);
void DisplayPlayerLife(Arena* arena, sf::RenderWindow& window);
void DisplayArena(Arena* arena, sf::RenderWindow& window);
void DisplayEnemies(Arena* arena, sf::RenderWindow& window);
void DisplayBullet(Arena* arena, sf::RenderWindow& window);
void DisplayWeaponInfo(Arena* arena, sf::RenderWindow& window);
void DisplayWeapons(Arena* arena, sf::RenderWindow& window);
void DisplayLoose(Arena* arena, sf::RenderWindow& window, Game* game);
void DisplayWin(Arena* arena, sf::RenderWindow& window, Game* game);
void DisplayWave(Arena* arena, sf::RenderWindow& window);
void DisplayBackground(Arena* arena, sf::RenderWindow& window);