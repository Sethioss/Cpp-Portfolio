#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "game.h"
#include <vector>
struct Game; 
struct Enemy;
struct Bullet;
struct Player;
struct Weapon;

using namespace std;

struct Arena
{
	sf::RectangleShape wallTop;
	sf::RectangleShape wallBot;
	sf::RectangleShape wallLeft;
	sf::RectangleShape wallRight;

	sf::Sprite background;

	int currentWave = 0;

	Player* player;
	vector<Enemy*> enemyList;
	vector<Bullet*> bulletList;
	vector<Weapon*> newWeaponList;
	
	bool canSpawn = true;
	float spawnTimer = 0;
};


Arena* CreateArena(Player* player, sf::RenderWindow& window);

void CheckCollisions(Arena* arena, Player* player, sf::RenderWindow& window, float deltaTime, Game* game);

void PlayerCollision(Arena* arena);
void EnemiesCollision(Arena* arena, float deltaTime);
void BulletsCollision(Arena* arena);
void WallCollisionPlayer(Arena* arena);
void WallCollisionEnemy(Arena* arena);
void WeaponCollision(Arena* arena, Game* game);
void KnockbackCollision(Arena* arena, sf::RenderWindow& window);

