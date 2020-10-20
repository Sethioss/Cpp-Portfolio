#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Weapons.h"
#include "arena.h"
#include "game.h"
struct Game;
struct Weapon;
struct Arena;

using namespace std;

struct Player
{
	string name = "Roger";
	int health = 100;
	float speedMove = 1;

	float minSpeed = 2;
	float maxSpeed = 4;

	sf::Vector2f knockbackDir;

	Weapon* oldWeapon = nullptr;
	Weapon* currentWeapon = nullptr;

	/*int xp = 0;
	int lvl = 1;*/

	bool isRunning = false;
	bool isInvicible = false;
	int invincibilityTimer = 2;
	bool canMove = true;
	bool isShooting = false;

	bool newWeaponCreated = false;
	bool canSwap = true;
	float swapTime = 0;

	sf::CircleShape playerShape;

	// Constructor
	Player(std::string Name_, int Health_, float SpeedMove) : name(Name_), health(Health_), speedMove(SpeedMove){}
};

Player* CreatePlayer(string name, int health, float speed);
void UpdatePlayer(Player* player, Arena* arena, sf::RenderWindow& window, float deltaTime, Game* game);
void DisplayInfo(Player* player);
void Move(Player* Roger, Arena* arena, float deltaTime);
void Shoot(Player* player, Weapon* weapon, Arena* arena, sf::RenderWindow& window, float deltaTime, Game* game);
sf::Vector2f GetPlayerCenter(Player* player);
sf::Vector2f GetAimDirNorm(Player* player, sf::RenderWindow& window);
void Knockback(Player* player, sf::RenderWindow& window, float knockback, float deltaTime);
void SwapWeapon(Arena* arena);
void CheckPlayerStates(Player* player, float deltaTime);
void CheckShoot(Arena* arena, Player* player, sf::RenderWindow& window, float deltaTime);
void LookAtMouse(Player* player, sf::RenderWindow& window);