#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "display.h"
#include "utility.h"

using namespace std;
 
// --- Affiche le joueur et son arme --- // 
void DisplayPlayer(Arena* arena, sf::RenderWindow& window)
{
	window.draw(arena->player->playerShape);
	window.draw(arena->player->currentWeapon->weaponShape);

	// Affiche l'arme à l'écran //
	arena->player->currentWeapon->weaponShape.setScale(2, 1);
	arena->player->currentWeapon->weaponShape.setOrigin(arena->player->currentWeapon->weaponShape.getSize().x, arena->player->currentWeapon->weaponShape.getSize().y / 2);
	arena->player->currentWeapon->weaponShape.setPosition(arena->player->playerShape.getPosition().x, arena->player->playerShape.getPosition().y);
}

// --- Affiche la vie du joueur --- //
void DisplayPlayerLife(Arena* arena, sf::RenderWindow& window)
{
	int posWindowX = window.getSize().x;
	int posWindowY = window.getSize().y;

	sf::Text health;
	sf::Font robotoFont;
	robotoFont.loadFromFile(getAssetsPath(getAppPath().append("Assets\\Roboto.ttf")));

	health.setFont(robotoFont);
	health.setCharacterSize(25);
	health.setFillColor(sf::Color::White);
	health.setString(to_string(arena->player->health));
	health.setPosition(145, 30);



		sf::RectangleShape healthBar;
		sf::RectangleShape healthBarEmpty;
		healthBar.setPosition(sf::Vector2f(40, 30));
		healthBarEmpty.setPosition(sf::Vector2f(40, 30));
		healthBarEmpty.setSize(sf::Vector2f(100, 30));
		healthBar.setSize(sf::Vector2f(arena->player->health, 30));

		healthBarEmpty.setFillColor(sf::Color(213, 45, 15));
		healthBar.setFillColor(sf::Color(2, 214, 124));

		window.draw(healthBarEmpty);
		window.draw(healthBar);

		if (arena->player->health <= 0) 
		{
			health.setString("LOSER");
		}
		

	window.draw(health);

}

// --- Affiche l'arène --- //
void DisplayArena(Arena* arena, sf::RenderWindow& window) 
{
	window.draw(arena->wallTop);
	window.draw(arena->wallLeft);
	window.draw(arena->wallRight);
	window.draw(arena->wallBot);
}

// --- Affiche les balles --- //
void DisplayBullet(Arena* arena, sf::RenderWindow& window)
{
	if (!arena->bulletList.empty())
	{
		for (int i = 0; i < arena->bulletList.size(); i++)
		{
			window.draw(arena->bulletList[i]->bulletShape);
		}
	}
}

// --- Affiche les ennemis --- //
void DisplayEnemies(Arena* arena, sf::RenderWindow& window)
{
	if (!arena->enemyList.empty())
	{
		for (int i = 0; i < arena->enemyList.size(); i++)
		{
			window.draw(arena->enemyList[i]->enemyShape);
			window.draw(arena->enemyList[i]->life1);
			window.draw(arena->enemyList[i]->life2);
			window.draw(arena->enemyList[i]->life3);

			// --- Affiche l'état de l'ennmi --- //
			if (arena->enemyList[i]->currenState != Enemy::ENEMY_STATE::Normal) 
			{
				sf::Font robotoFont;
				robotoFont.loadFromFile(getAssetsPath(getAppPath().append("Assets\\Roboto.ttf")));

				arena->enemyList[i]->effectDisplay.setFont(robotoFont);
				arena->enemyList[i]->effectDisplay.setCharacterSize(20);
				//arena->enemyList[i]->effectDisplay.setFillColor(sf::Color::Yellow);
				arena->enemyList[i]->effectDisplay.setString(arena->enemyList[i]->effectName);
				arena->enemyList[i]->effectDisplay.setPosition(arena->enemyList[i]->enemyShape.getPosition().x - arena->enemyList[i]->effectDisplay.getGlobalBounds().width / 4, arena->enemyList[i]->enemyShape.getPosition().y - 50);

				window.draw(arena->enemyList[i]->effectDisplay);
			}

			if (arena->enemyList[i]->enemyType == Enemy::ENEMY_TYPE::Stalker) 
			{
			window.draw(arena->enemyList[i]->life4);
			}

			if (arena->enemyList[i]->enemyType == Enemy::ENEMY_TYPE::Boomer) 
			{
			window.draw(arena->enemyList[i]->life4);
			window.draw(arena->enemyList[i]->life5);
			window.draw(arena->enemyList[i]->life6);
			}

		}
	}
}


void DisplayWeapons(Arena* arena, sf::RenderWindow& window) 
{
	if (!arena->newWeaponList.empty())
	{
		for (int i = 0; i < arena->newWeaponList.size(); i++)
		{
			window.draw(arena->newWeaponList[i]->weaponShape);
		}
	}
}

// --- Affiche les informations de l'arme et le nombre de munition à l'écran --- //
void DisplayWeaponInfo(Arena* arena, sf::RenderWindow& window) 
{
	int posWindowX = window.getSize().x;
	int posWindowY = window.getSize().y;
	
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(143, 139, 126, 95));
	rect.setOutlineThickness(4);
	rect.setOutlineColor(sf::Color(255, 232, 144, 95));

	if (arena->player->oldWeapon != nullptr) 
	{
		rect.setPosition(28, posWindowY - 135);
		rect.setSize(sf::Vector2f(200, 115));
	}
	else 
	{	
		rect.setSize(sf::Vector2f(200, 80));
		rect.setPosition(28, posWindowY - 110);
	}
	

	sf::Text oldWeaponName;
	sf::Text weaponName;
	sf::Text weaponAmmo;
	sf::Font robotoFont;
	robotoFont.loadFromFile(getAssetsPath(getAppPath().append("Assets\\Roboto.ttf")));

	weaponName.setFont(robotoFont);
	weaponName.setCharacterSize(25);
	weaponName.setFillColor(sf::Color(245, 222, 110));
	weaponName.setString("--> " + arena->player->currentWeapon->name);

	if (arena->player->oldWeapon != nullptr) 
	{
	oldWeaponName = weaponName;
	oldWeaponName.setFillColor(sf::Color(240, 237, 221));
	oldWeaponName.setString(arena->player->oldWeapon->name +" "+ to_string(arena->player->oldWeapon->ammo));
	}
	
	weaponAmmo.setFont(robotoFont);
	weaponAmmo.setCharacterSize(25);
	weaponAmmo.setFillColor(sf::Color::White);
	weaponAmmo.setString("Ammo : " + to_string(arena->player->currentWeapon->ammo));

	weaponName.setPosition(30, posWindowY - 90);
	oldWeaponName.setPosition(30, posWindowY - 125);
	weaponAmmo.setPosition(50, posWindowY - 60);

	window.draw(rect);
	window.draw(weaponName);
	window.draw(weaponAmmo);
	window.draw(oldWeaponName);
}

// --- Affiche l'écran de loose --- //
void DisplayLoose(Arena* arena, sf::RenderWindow& window, Game* game)
{
	int posWindowX = window.getSize().x;
	int posWindowY = window.getSize().y;

	sf::Text looseText;
	sf::Font robotoFont;

	robotoFont.loadFromFile(getAssetsPath(getAppPath().append("Assets\\Roboto.ttf")));

	looseText.setFont(robotoFont);
	looseText.setString("You lose");
	looseText.setCharacterSize(120);
	looseText.setFillColor(sf::Color::Red);

	looseText.setOrigin(looseText.getLocalBounds().width / 2, looseText.getLocalBounds().height);

	//looseText.setPosition(100, 100);
	looseText.setPosition(posWindowX / 2, posWindowY / 2);

	window.draw(looseText);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		game->gameOver = true;
	}
}

void DisplayWin(Arena* arena, sf::RenderWindow& window, Game* game)
{
	int posWindowX = window.getSize().x;
	int posWindowY = window.getSize().y;

	sf::Text winText;
	sf::Font robotoFont;

	robotoFont.loadFromFile(getAssetsPath(getAppPath().append("Assets\\Roboto.ttf")));

	winText.setFont(robotoFont);
	winText.setString("You win");
	winText.setCharacterSize(70);
	winText.setPosition(posWindowX / 2, posWindowY / 2);

	winText.setOrigin(winText.getLocalBounds().width / 2, winText.getLocalBounds().height);


	window.draw(winText);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		game->gameOver = true;
	}
}
void DisplayWave(Arena* arena, sf::RenderWindow& window) 
{
	int posWindowX = window.getSize().x;
	int posWindowY = window.getSize().y;

	sf::Text waveText;
	sf::Font robotoFont;

	robotoFont.loadFromFile(getAssetsPath(getAppPath().append("Assets\\Roboto.ttf")));

	waveText.setFont(robotoFont);
	if (!arena->enemyList.empty()) 
	{
	waveText.setString("Wave : " + to_string(arena->currentWave - 1));
	}
	else 
	{
		int spawnTime = arena->spawnTimer;
		waveText.setString("/-- Next Wave in : " + to_string(spawnTime + 1) + " --/");
	}

	waveText.setCharacterSize(25);
	waveText.setPosition(posWindowX / 2, 55);

	waveText.setOrigin(waveText.getLocalBounds().width / 2, waveText.getLocalBounds().height);


	window.draw(waveText);
}