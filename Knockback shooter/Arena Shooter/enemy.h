#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "arena.h"
struct Arena;
struct Player;


using namespace std;

struct Enemy
{
	float health = 40;
	int damage;
	
	float moveSpeed = 2;
	float currentSpeed = 2;
	Player* target = nullptr;
	
	sf::RectangleShape enemyShape;
	sf::CircleShape life1;
	sf::CircleShape life2;
	sf::CircleShape life3;
	sf::CircleShape life4;
	sf::CircleShape life5;
	sf::CircleShape life6;

	enum ENEMY_TYPE
	{
		Stalker,
		Boomer,
		Lost,
		Shooter
	};

	enum ENEMY_STATE
	{
		Normal,
		Enraged,
		Stunned,
		Confused,
		Burning
	};

	ENEMY_STATE currenState = Enemy::ENEMY_STATE::Normal;
	ENEMY_TYPE enemyType = Enemy::ENEMY_TYPE::Stalker;
	sf::Color baseColor;

	float effectTime = 0;
	sf::Text effectDisplay;
	string effectName = "";
	bool canMove = true;

	// Constructor
	Enemy(int Damage_, float SpeedMove_, Player* Player_) : damage(Damage_), moveSpeed(SpeedMove_), target(Player_) {}
};

Enemy* CreateEnemy(int damage, float speedMove, Enemy::ENEMY_TYPE enemyType, Player* player, Arena* arena, sf::RenderWindow& window);
void UpdateEnemy(Arena* arena, sf::RenderWindow& window, float deltaTime);
void EnemyWaves(Arena* arena, sf::RenderWindow& window, float deltaTime);
void Move(Enemy* enemy, float posX, float posY, float deltaTime);
void CheckType(Enemy* enemy, float deltaTime);
void Stalk(Enemy* enemy, float deltaTime);
void CheckEnemyState(Arena* arena, float deltaTime);
void CheckEnemyLife(Arena* arena);