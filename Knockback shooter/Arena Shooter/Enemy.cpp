#include <iostream>
#include <SFML/Graphics.hpp>
#include "utility.h"
#include "enemy.h"
#include "arena.h"

using namespace std;

// --- Met à jour les informations des ennemis pour chaque boucle de jeu --- //
void UpdateEnemy(Arena* arena, sf::RenderWindow& window, float deltaTime)
{
	EnemyWaves(arena, window, deltaTime);

	for (int i = 0; i < arena->enemyList.size(); i++)
	{
		Enemy* updateEnemy = arena->enemyList[i];

		//Move(updateEnemy, arena->player->playerShape.getPosition().x, arena->player->playerShape.getPosition().y, deltaTime);
		CheckType(updateEnemy, deltaTime);
		CheckEnemyState(arena, deltaTime);
		CheckEnemyLife(arena);
	}
}

// --- Créer un ennemi et défini sa taille, sa couleur et sa position --- //
Enemy* CreateEnemy(int damage, float speedMove, Enemy::ENEMY_TYPE enemyType, Player* player, Arena* arena, sf::RenderWindow& window)
{
	Enemy* createEnemy = new Enemy(damage, speedMove, player);
	createEnemy->enemyShape.setSize(sf::Vector2f(50, 50));
	createEnemy->enemyShape.setFillColor(sf::Color(92, 255, 92));
	createEnemy->baseColor = sf::Color(92, 255, 92);
	createEnemy->enemyShape.setPosition(Random(window.getSize().x - 50), Random(window.getSize().y - 50));
	createEnemy->enemyType = enemyType;

	createEnemy->life1.setFillColor(sf::Color(174, 255, 82));
	createEnemy->life1.setRadius(8);
	createEnemy->life1.setPointCount(6);

	createEnemy->life2 = createEnemy->life1;
	createEnemy->life3 = createEnemy->life2;
	createEnemy->life4 = createEnemy->life3;

	if (createEnemy->enemyType == Enemy::ENEMY_TYPE::Boomer)
	{
		createEnemy->life5 = createEnemy->life4;
		createEnemy->life6 = createEnemy->life5;
		createEnemy->health = 60;
		createEnemy->damage = 20;
		createEnemy->moveSpeed = 1;
		createEnemy->baseColor = sf::Color(60, 143, 60);
	}

	if (createEnemy->enemyType == Enemy::ENEMY_TYPE::Lost)
	{
		createEnemy->health = 30;
		createEnemy->damage = 10;
		createEnemy->moveSpeed = 1.5f;
		createEnemy->baseColor = sf::Color(142, 186, 145);
	}
	arena->enemyList.push_back(createEnemy);

	return createEnemy;
}

// --- Gère les vagues d'ennemis --- //
void EnemyWaves(Arena* arena, sf::RenderWindow& window, float deltaTime)
{
	if (arena->enemyList.empty() && arena->currentWave <= 5 && arena->canSpawn)
	{

		int spawnEnemy = arena->currentWave * 1;
		for (int i = 0; i < spawnEnemy; i++)
		{
			CreateEnemy(10, 2.5f, Enemy::ENEMY_TYPE::Stalker, arena->player, arena, window);
		}
		if (arena->currentWave == 2) 
		{
			CreateEnemy(20, 1.5f, Enemy::ENEMY_TYPE::Boomer, arena->player, arena, window);
		}
		if (arena->currentWave == 3) 
		{
			CreateEnemy(10, 1.5f, Enemy::ENEMY_TYPE::Lost, arena->player, arena, window);
		}
		if (arena->currentWave == 4) 
		{
			CreateEnemy(20, 1.5f, Enemy::ENEMY_TYPE::Boomer, arena->player, arena, window);
			CreateEnemy(10, 1, Enemy::ENEMY_TYPE::Lost, arena->player, arena, window);
		}
		if (arena->currentWave == 5) 
		{
			CreateEnemy(20, 1.5f, Enemy::ENEMY_TYPE::Boomer, arena->player, arena, window);
			CreateEnemy(20, 1.5f, Enemy::ENEMY_TYPE::Boomer, arena->player, arena, window);
			CreateEnemy(10, 1, Enemy::ENEMY_TYPE::Lost, arena->player, arena, window);
		}

		arena->currentWave++;
		arena->canSpawn = false;
		arena->spawnTimer = 5;
	}

	if (arena->enemyList.empty() && !arena->canSpawn) 
	{
		if (arena->spawnTimer > 0) 
		{
			arena->spawnTimer -= deltaTime;
		}
		else 
		{
			arena->canSpawn = true;
		}
	}
}


// --- Applique les effets à l'ennemi suivant son type --- //
void CheckType(Enemy* enemy, float deltaTime)
{
	float posX = enemy->target->playerShape.getPosition().x;
	float posY = enemy->target->playerShape.getPosition().y;

	sf::Vector2f posPlayer(posX, posY);
	sf::Vector2f posEnemy = enemy->enemyShape.getPosition();
	sf::Vector2f dirEtoP = posPlayer - posEnemy;
	sf::Vector2f dir = normalise(dirEtoP);

	sf::Vector2f deltaPos = dir * (enemy->currentSpeed * 25) * deltaTime;

	if (enemy->enemyType == Enemy::ENEMY_TYPE::Stalker)
	{
		enemy->life1.setPosition(enemy->enemyShape.getPosition().x - 15, enemy->enemyShape.getPosition().y - 25);
		enemy->life2.setPosition(enemy->enemyShape.getPosition().x + 5, enemy->enemyShape.getPosition().y - 25);
		enemy->life3.setPosition(enemy->enemyShape.getPosition().x + 25, enemy->enemyShape.getPosition().y - 25);
		enemy->life4.setPosition(enemy->enemyShape.getPosition().x + 45, enemy->enemyShape.getPosition().y - 25);
	}
	if (enemy->canMove)
	{
		if (enemy->target != nullptr)
		{
			if (enemy->enemyShape.getPosition().x != posX && enemy->enemyShape.getPosition().y != posY)
			{
				enemy->enemyShape.move(deltaPos);
			}
		}

	}

	// --- L'ennemi traque le joueur et est plus fort --- //
	if (enemy->enemyType == Enemy::ENEMY_TYPE::Boomer)
	{
		if (enemy->canMove)
		{
			if (enemy->target != nullptr)
			{
				if (enemy->enemyShape.getPosition().x != posX && enemy->enemyShape.getPosition().y != posY)
				{
					enemy->enemyShape.move(deltaPos);

					enemy->life1.setPosition(enemy->enemyShape.getPosition().x - 35, enemy->enemyShape.getPosition().y - 25);
					enemy->life2.setPosition(enemy->enemyShape.getPosition().x - 15, enemy->enemyShape.getPosition().y - 25);
					enemy->life3.setPosition(enemy->enemyShape.getPosition().x + 5, enemy->enemyShape.getPosition().y - 25);
					enemy->life4.setPosition(enemy->enemyShape.getPosition().x + 25, enemy->enemyShape.getPosition().y - 25);
					enemy->life5.setPosition(enemy->enemyShape.getPosition().x + 45, enemy->enemyShape.getPosition().y - 25);
					enemy->life6.setPosition(enemy->enemyShape.getPosition().x + 65, enemy->enemyShape.getPosition().y - 25);
				}
			}
		}
	}

	// --- Ere aléatoirement sur l'écran --- //
	if (enemy->enemyType == Enemy::ENEMY_TYPE::Lost)
	{
		enemy->life1.setPosition(enemy->enemyShape.getPosition().x - 5, enemy->enemyShape.getPosition().y - 25);
		enemy->life2.setPosition(enemy->enemyShape.getPosition().x + 15, enemy->enemyShape.getPosition().y - 25);
		enemy->life3.setPosition(enemy->enemyShape.getPosition().x + 35, enemy->enemyShape.getPosition().y - 25);

		if (enemy->canMove)
		{
			int caseNumber = Random(1);

			float moveX;
			float moveY;

			if (caseNumber == 0)
			{
				moveX = Random(200) * deltaTime * (enemy->moveSpeed / 2);
				moveY = Random(200) * deltaTime * (enemy->moveSpeed / 2);
			}

			if (caseNumber == 1)
			{
				moveX = -1 * Random(200) * deltaTime * (enemy->moveSpeed / 2);
				moveY = -1 * Random(200) * deltaTime * (enemy->moveSpeed / 2);
			}
			enemy->enemyShape.move(moveX, moveY);
		}
		else if(!enemy->canMove)
		{
			enemy->enemyShape.move(0, 0);
		}
	}
}


// --- Check l'état des ennemis et mets à jour son état s'il en a un --- //
void CheckEnemyState(Arena* arena, float deltaTime)
{
	for (int i = 0; i < arena->enemyList.size(); i++)
	{
		Enemy* thisEnemy = arena->enemyList[i];

		if (thisEnemy->currenState == Enemy::ENEMY_STATE::Normal)
		{
			thisEnemy->enemyShape.setFillColor(sf::Color::Green);
			thisEnemy->currentSpeed = thisEnemy->moveSpeed * 1;
			thisEnemy->enemyShape.setFillColor(thisEnemy->baseColor);
			thisEnemy->effectName = "";
		}
		if (thisEnemy->currenState == Enemy::ENEMY_STATE::Confused)
		{
			thisEnemy->enemyShape.setFillColor(sf::Color::Magenta);
			thisEnemy->currentSpeed = thisEnemy->moveSpeed * -1.5f;

			thisEnemy->effectDisplay.setFillColor(sf::Color::Magenta);
			thisEnemy->effectName = "Confused";
		}
		if (thisEnemy->currenState == Enemy::ENEMY_STATE::Stunned)
		{
			thisEnemy->enemyShape.setFillColor(sf::Color::Cyan);
			thisEnemy->currentSpeed = thisEnemy->canMove = false;

			thisEnemy->effectDisplay.setFillColor(sf::Color::Cyan);
			thisEnemy->effectName = "Stunned";
		}
		if (thisEnemy->currenState == Enemy::ENEMY_STATE::Enraged)
		{
			thisEnemy->enemyShape.setFillColor(sf::Color::Red);
			thisEnemy->currentSpeed = thisEnemy->moveSpeed * 3;

			thisEnemy->effectDisplay.setFillColor(sf::Color::Red);
			thisEnemy->effectName = "Enraged";
		}
		if (thisEnemy->currenState == Enemy::ENEMY_STATE::Burning)
		{
			thisEnemy->enemyShape.setFillColor(sf::Color::Yellow);
			thisEnemy->currentSpeed = thisEnemy->moveSpeed * -3;

			thisEnemy->effectDisplay.setFillColor(sf::Color(245, 182, 46));
			thisEnemy->effectName = "Burning";
			thisEnemy->health -= 0.1f;
		}

		if (thisEnemy->effectTime > 0)
		{
			thisEnemy->effectTime -= deltaTime;
		}
		else
		{
			thisEnemy->currenState = Enemy::Normal;
		}
	}
}

void CheckEnemyLife(Arena* arena)
{
	for (int i = 0; i < arena->enemyList.size(); i++)
	{
		Enemy* thisEnemy = arena->enemyList[i];
		
		sf::Color emptyColor = sf::Color(234, 46, 21);

		if (thisEnemy->enemyType == Enemy::ENEMY_TYPE::Stalker)
		{
			if (thisEnemy->health <= 30) { thisEnemy->life4.setFillColor(emptyColor); }
			if (thisEnemy->health <= 20) { thisEnemy->life3.setFillColor(emptyColor); }
			if (thisEnemy->health <= 10) { thisEnemy->life2.setFillColor(emptyColor); }
			if (thisEnemy->health < 0) { thisEnemy->life1.setFillColor(emptyColor); }
		}
		if (thisEnemy->enemyType == Enemy::ENEMY_TYPE::Boomer)
		{
			cout << thisEnemy->health << endl;
			if (thisEnemy->health <= 50) { thisEnemy->life6.setFillColor(emptyColor); }
			if (thisEnemy->health <= 40) { thisEnemy->life5.setFillColor(emptyColor); }
			if (thisEnemy->health <= 31) { thisEnemy->life4.setFillColor(emptyColor); }
			if (thisEnemy->health <= 20) { thisEnemy->life3.setFillColor(emptyColor); }
			if (thisEnemy->health <= 10) { thisEnemy->life2.setFillColor(emptyColor); }
			if (thisEnemy->health < 0) { thisEnemy->life1.setFillColor(emptyColor); }
		}
		if (thisEnemy->enemyType == Enemy::ENEMY_TYPE::Lost)
		{
			if (thisEnemy->health <= 20) { thisEnemy->life3.setFillColor(emptyColor); }
			if (thisEnemy->health <= 10) { thisEnemy->life2.setFillColor(emptyColor); }
			if (thisEnemy->health < 0) { thisEnemy->life1.setFillColor(emptyColor); }
		}

		if (arena->enemyList.size() > 1 && arena->enemyList[i]->health <= 0)
		{
			arena->enemyList.erase(arena->enemyList.begin() + i);
		}
		else if (arena->enemyList.size() == 1 && arena->enemyList[0]->health <= 0)
		{
			arena->enemyList.erase(arena->enemyList.begin());
		}
	}
}