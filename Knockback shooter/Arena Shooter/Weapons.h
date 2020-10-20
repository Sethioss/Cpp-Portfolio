#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include"bullet.h"
#include <vector>

struct Arena;
struct Bullet;
struct ShotGunBullet;
struct MachineGunBullet;

using namespace std;


class Weapon
{
public :

	std::string name;
	int ammo;
	int maxAmmo;
	int damage; 
	float cadency; 
	float cooldown = cadency;
	bool canShoot = true;
	float knockBackSpeed;
	float knockbackDamping;
	vector<Bullet*> chamber;
	string weaponSound;	

	sf::CircleShape bulletShape;
	sf::RectangleShape weaponShape;

	Weapon(std::string name_, int ammo_, int maxAmmo_, int Damage_, float cadency_, float knockBack_, float knockBackDamping_, string weaponSound_) :
		name(name_), ammo(ammo_), maxAmmo(maxAmmo_), damage(Damage_), cadency(cadency_), knockBackSpeed(knockBack_), knockbackDamping(knockBackDamping_), weaponSound(weaponSound_)
	{}
	Weapon() {}
	//void Fire(int& ammo, knockBack);

	void WeaponDesc(std::string name, int ammo, int damage, float cadency, float knockBack)
	{
		std::cout << "Weapon : " << name << " Damage : " << damage << 
		" Cadency  : " << cadency << " Knockback  : " << knockBack << std::endl;
	}
};



Weapon* CreateWeapon(string name, int ammo, int maxAmmo, int damage, int cadency, float knowback, float knockBackDamping, string weaponSound);
Weapon* InstantiateWeapon();
void GenerateWeaponOnField(Arena* arena, sf::RenderWindow& window);
