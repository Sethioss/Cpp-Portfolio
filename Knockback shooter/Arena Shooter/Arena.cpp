#include <iostream>
#include <vector>
#include "arena.h"
#include "utility.h"
struct Arena;
struct Game;

using namespace std;

// --- Créer l'arene et ses paramètres --- //
Arena* CreateArena(Player* player, sf::RenderWindow& window) 
{
	int posX = window.getSize().x;
	int posY = window.getSize().y;
	int wallThick = 20;
	sf::Color wallColor = sf::Color(199, 151, 91);

	Arena* createArena = new Arena();


	createArena->wallTop.setFillColor(wallColor);
	createArena->wallLeft.setFillColor(wallColor);
	createArena->wallRight.setFillColor(wallColor);
	createArena->wallBot.setFillColor(wallColor);

	//Setup Wall Top
	createArena->wallTop.setSize(sf::Vector2f(posX, wallThick));

	//Setup Wall Bot
	createArena->wallBot.setSize(sf::Vector2f(posX, wallThick));
	createArena->wallBot.setPosition(sf::Vector2f(0, posY - wallThick));

	//Setup Wall Left
	createArena->wallLeft.setSize(sf::Vector2f(wallThick, posY));
	
	//Setup Wall Right
	createArena->wallRight.setSize(sf::Vector2f(wallThick, posY));
	createArena->wallRight.setPosition(sf::Vector2f(posX - wallThick, 0));
	
	createArena->player = player;

	return createArena;
}

// --- Actualise toutes les collisions --- //
void CheckCollisions(Arena* arena, Player* player, sf::RenderWindow& window, float deltaTime, Game* game)
{
	PlayerCollision(arena);
	EnemiesCollision(arena, deltaTime);
	BulletsCollision(arena);
	WallCollisionPlayer(arena);
	WallCollisionEnemy(arena);
	WeaponCollision(arena, game);
	KnockbackCollision(arena, window);
}

// --- Detection des collisions entre le joueur et chaque ennemis --- //
void PlayerCollision(Arena* arena)
{
	if (!arena->enemyList.empty())
	{
		// --- Detection ds collisions entre le joueur et chaque ennemis --- //
		for (int i = 0; i < arena->enemyList.size(); i++)
		{
			if (arena->player->playerShape.getGlobalBounds().intersects(arena->enemyList[i]->enemyShape.getGlobalBounds()))
			{
				if (!arena->player->isInvicible)
				{
					cout << "OOF" << endl;
					arena->player->health -= arena->enemyList[i]->damage;
					DisplayInfo(arena->player);

					arena->player->playerShape.setFillColor(sf::Color::Red);
					arena->player->isInvicible = true;
				}
			}
		}
	}
}

// --- Detection des collisions entre les ennemis et les ennemis --- //
void EnemiesCollision(Arena* arena, float deltaTime) 
{
	if (!arena->enemyList.empty())
	{
		for (int i = 0; i < arena->enemyList.size(); i++)
		{
			for (int k = 0; k < arena->enemyList.size(); k++)
			{
				if (arena->enemyList[i] != arena->enemyList[k]) 
				{
					int bump = 5;

					if (arena->enemyList[i]->canMove)
					{
						if (arena->enemyList[i]->enemyShape.getGlobalBounds().intersects(arena->enemyList[k]->enemyShape.getGlobalBounds()))
						{
							if (arena->enemyList[i]->currenState == Enemy::ENEMY_STATE::Burning)
							{
								arena->enemyList[k]->currenState = arena->enemyList[i]->currenState;
							}

							arena->enemyList[i]->canMove = false;
							arena->enemyList[i]->enemyShape.move(sf::Vector2f(-bump, -bump));
							arena->enemyList[k]->enemyShape.move(sf::Vector2f(bump, bump));
						}
						else { arena->enemyList[i]->canMove = true; }
					}
				}
				}
			}
		}
	}



// --- Detection des collisions entre chaque balles présentes dans la list "Bullet" --- //
void BulletsCollision(Arena* arena) 
{
	int enemyListRange = arena->enemyList.size();
	int bulletListRange = arena->bulletList.size();
	Bullet::BULLET_EFFECT tempEffect;

	if (!arena->enemyList.empty() && !arena->bulletList.empty()) 
	{
		for (size_t k = 0; k < arena->enemyList.size(); ++k)
		{
			for (size_t i = 0; i < arena->bulletList.size(); ++i)
			{
				if (arena->bulletList[i]->bulletShape.getGlobalBounds().intersects(arena->enemyList[k]->enemyShape.getGlobalBounds()))
				{
					tempEffect = arena->bulletList[i]->bulletEffect;

					if (tempEffect == Bullet::BULLET_EFFECT::Normal)
					{ arena->enemyList[k]->currenState = Enemy::ENEMY_STATE::Normal; }
					if (tempEffect == Bullet::BULLET_EFFECT::Confuse) 
					{ arena->enemyList[k]->currenState = Enemy::ENEMY_STATE::Confused; 
					arena->enemyList[k]->effectTime = 3.0f;
					}
					if (tempEffect == Bullet::BULLET_EFFECT::Stun) 
					{
						arena->enemyList[k]->currenState = Enemy::ENEMY_STATE::Stunned; 
						arena->enemyList[k]->effectTime = 2.0f;
					}
					if (tempEffect == Bullet::BULLET_EFFECT::Enrage) 
					{
						arena->enemyList[k]->currenState = Enemy::ENEMY_STATE::Enraged; 
						arena->enemyList[k]->effectTime = 3.0f;
					}
					if (tempEffect == Bullet::BULLET_EFFECT::Burn) 
					{
						arena->enemyList[k]->currenState = Enemy::ENEMY_STATE::Burning;
						arena->enemyList[k]->effectTime = 2.0f;
					}

					if (arena->bulletList[i] != nullptr) 
					{
						if (arena->enemyList[k] != nullptr) 
						{
							arena->enemyList[k]->health -= arena->bulletList[i]->bulletDamage;
							arena->bulletList.erase(arena->bulletList.begin() + i);
						}
					}
				}
			}
		}
	}
}

// --- Detection des collisions entre le joueur et le mur --- //
void WallCollisionPlayer(Arena* arena) 
{
	if (arena->wallTop.getGlobalBounds().intersects(arena->player->playerShape.getGlobalBounds())) 
	{
		//cout << "Collision avec mur du haut" << endl;
		arena->player->playerShape.move(0, 10);
	}
	if (arena->wallBot.getGlobalBounds().intersects(arena->player->playerShape.getGlobalBounds())) 
	{
		//cout << "Collision avec mur du bas" << endl;
		arena->player->playerShape.move(0, -10);
	}
	if (arena->wallLeft.getGlobalBounds().intersects(arena->player->playerShape.getGlobalBounds()))
	{
		//cout << "Collision avec mur de gauche" << endl;
		arena->player->playerShape.move(10, 0);
	}
	if (arena->wallRight.getGlobalBounds().intersects(arena->player->playerShape.getGlobalBounds()))
	{
		//cout << "Collision avec mur de droite" << endl;
		arena->player->playerShape.move(-10, 0);
	}
}

void WeaponCollision(Arena* arena, Game* game)
{
	for (int i = 0; i < arena->newWeaponList.size(); i++)
	{
		if (arena->player->playerShape.getGlobalBounds().intersects(arena->newWeaponList[i]->weaponShape.getGlobalBounds()))
		{
			arena->player->oldWeapon = arena->player->currentWeapon;
			arena->player->currentWeapon = arena->newWeaponList[i];
			arena->newWeaponList.erase(arena->newWeaponList.begin() + i);
			arena->player->newWeaponCreated = false;

			game->audioToPlay = getAssetsPath(getAppPath().append("Assets\\weapon_change.wav"));
		}
	}
}

// --- Detection des collisions entre les ennemis et le mur --- //
void WallCollisionEnemy(Arena* arena) 
{
	for (int i = 0; i < arena->enemyList.size(); i++)
	{
		Enemy* checkEnemy = arena->enemyList[i];

		if (arena->wallTop.getGlobalBounds().intersects(checkEnemy->enemyShape.getGlobalBounds()))
		{
			checkEnemy->enemyShape.move(0, 10);
		}
		if (arena->wallBot.getGlobalBounds().intersects(checkEnemy->enemyShape.getGlobalBounds()))
		{
			checkEnemy->enemyShape.move(0, -10);
		}
		if (arena->wallLeft.getGlobalBounds().intersects(checkEnemy->enemyShape.getGlobalBounds()))
		{
			checkEnemy->enemyShape.move(10, 0);
		}
		if (arena->wallRight.getGlobalBounds().intersects(checkEnemy->enemyShape.getGlobalBounds()))
		{
			checkEnemy->enemyShape.move(-10, 0);
		}

		// A BOUGER
		if (arena->player->playerShape.getGlobalBounds().intersects(checkEnemy->enemyShape.getGlobalBounds())) 
		{
			checkEnemy->canMove = false;
		}
		else 
		{
			checkEnemy->canMove = true;
		}
	}
}

// --- Detection des collisions entre le mur et le joueur au moment du knowback --- //
void KnockbackCollision(Arena* arena, sf::RenderWindow& window) 
{
	int posPlayerX = arena->player->playerShape.getPosition().x;
	int posPlayerY = arena->player->playerShape.getPosition().y;
	int sizeWindowX = window.getSize().x;
	int sizeWindowY = window.getSize().y;

	if (posPlayerX < 0) { arena->player->playerShape.setPosition((posPlayerX) + 10, posPlayerY); }
	if (posPlayerX > sizeWindowX) { arena->player->playerShape.setPosition((posPlayerX) - 10, posPlayerY); }
	if (posPlayerY < 0) { arena->player->playerShape.setPosition(posPlayerX, (posPlayerY) + 10); }
	if (posPlayerY > sizeWindowY) { arena->player->playerShape.setPosition(posPlayerX, (posPlayerY) -10); }
}
