#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Weapons.h"
#include "utility.h"


using namespace std;

// --- Créer une arme --- //
Weapon* CreateWeapon(string name, int ammo, int maxAmmo, int damage, int cadency, float knowback, float knockBackDamping, string weaponSound)
{
	Weapon* createWeapon = new Weapon(name, ammo, maxAmmo, damage, cadency, knowback, knockBackDamping, weaponSound);
	createWeapon->weaponShape.setSize(sf::Vector2f(25, 25));
	createWeapon->weaponShape.setFillColor(sf::Color::Blue);

	return createWeapon;
}

// --- Instantie une arme aléatoirement suivant plusieurs critères --- //
Weapon* InstantiateWeapon()
{
	// --- Random Range (0 -> nombre d'armes) --- //
	//UpdateRandom();
	int totalWeapon = 5;
	int sortedWeapon = Random(totalWeapon - 1);
	cout << "sortedWeapon : " << sortedWeapon << endl;
	//sortedWeapon = 4;
	
	if (sortedWeapon == 0)
	{
		Weapon* createWeapon = new Weapon("Gun", 12, 12, 10, 0.25f, 0.7, 2, getAssetsPath(getAppPath().append("Assets\\sh_pistol.wav")));
		createWeapon->weaponShape.setSize(sf::Vector2f(25, 25));
		createWeapon->weaponShape.setFillColor(sf::Color::Blue);
		FillWeapon(createWeapon, 10, 420, 1.5f, Bullet::BULLET_EFFECT::Normal);
		return createWeapon;
	}
	if (sortedWeapon == 1)
	{
		Weapon* createWeapon = new Weapon("Shotgun", 6, 6, 30, 0.5f, 2, 1.4, getAssetsPath(getAppPath().append("Assets\\sh_shotgun.wav")));
		createWeapon->weaponShape.setSize(sf::Vector2f(25, 25));
		createWeapon->weaponShape.setFillColor(sf::Color::Magenta);
		FillWeapon(createWeapon, 12, 350, 1.2f, Bullet::BULLET_EFFECT::Confuse);
		return createWeapon;
	}
	if (sortedWeapon == 4)
	{
		Weapon* createWeapon = new Weapon("Machinegun", 20, 20, 10, 0.08f, 0.2f, 1.8f, getAssetsPath(getAppPath().append("Assets\\sh_machinegun.wav")));
		createWeapon->weaponShape.setSize(sf::Vector2f(25, 25));
		createWeapon->weaponShape.setFillColor(sf::Color::Red);
		FillWeapon(createWeapon, 8, 450, 3, Bullet::BULLET_EFFECT::Enrage);
		return createWeapon;
	}
	if (sortedWeapon == 2) 
	{
		Weapon* createWeapon = new Weapon("Stungun", 3, 3, 20, 0.7f, 1.2f, 4, getAssetsPath(getAppPath().append("Assets\\sh_stungun.wav")));
		createWeapon->weaponShape.setSize(sf::Vector2f(25, 25));
		createWeapon->weaponShape.setFillColor(sf::Color::Cyan);
		FillWeapon(createWeapon, 7, 390, 1.3f, Bullet::BULLET_EFFECT::Stun);
	}
	if (sortedWeapon == 3) 
	{
		Weapon* createWeapon = new Weapon("Flamethrower", 20, 20, 0, 0.01f, 0.4, 4, getAssetsPath(getAppPath().append("Assets\\sh_flamethrower.wav")));
		createWeapon->weaponShape.setSize(sf::Vector2f(25, 25));
		createWeapon->weaponShape.setFillColor(sf::Color(245, 182, 46));
		FillWeapon(createWeapon, 15, 500, 1, Bullet::BULLET_EFFECT::Burn);
	}
}

	void GenerateWeaponOnField(Arena* arena, sf::RenderWindow& window) 
	{
		int sizeWindowX = window.getSize().x;
		int sizeWindowY = window.getSize().y;

		int randX = Random(sizeWindowX);
		int randY = Random(sizeWindowY);

		Weapon* generatedWeapon = new Weapon();

		generatedWeapon = InstantiateWeapon();
		if (randX < 40) 
		{
			randX = 40;
		}
		if (randX > 1880) 
		{
			randX = 1880;
		}
		if (randY < 40) 
		{
			randY = 40;
		}
		if (randY > 1040) 
		{
			randY = 1040;
		}

		generatedWeapon->weaponShape.setPosition(randX, randY);
		//generatedWeapon->weaponShape.setPosition(100, 100);
		arena->newWeaponList.push_back(generatedWeapon);
	}