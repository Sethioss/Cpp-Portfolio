#pragma once
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include "Weapons.h"
#include "player.h"
struct Weapon;
struct Arena;

class Bullet
{
public:

	float size = 5;
	float maxSpeed = 20.f;
	float bulletDamage;
	float bulletEnd;

	sf::CircleShape bulletShape;
	sf::Vector2f currVelocity;

	enum BULLET_EFFECT
	{
		Normal,
		Stun,
		Confuse,
		Enrage,
		Burn
	};
	BULLET_EFFECT bulletEffect;


	Bullet(int damage_, float size_, float maxSpeed_, float bulletEnd_, BULLET_EFFECT bulletEffect_) : bulletDamage(damage_), currVelocity(0.f, 0.f), maxSpeed(maxSpeed_), bulletEnd(bulletEnd_), bulletEffect(bulletEffect_)
	{
		this->bulletShape.setRadius(size_);
		this->bulletShape.setPointCount(3);
		this->bulletShape.setOrigin(sf::Vector2f(size_, size));
		this->bulletShape.setFillColor(sf::Color::Blue);
	}
};

Bullet* InstantiateBullet(int damage, float bulletSize, float bulletSpeed, float durationBullet, Bullet::BULLET_EFFECT bulletEffect);
void UpdateBullet(Weapon* weapon, Arena* arena, sf::RenderWindow& window, float deltaTime);
void MoveBullet(Weapon* weapon, Arena* arena, sf::RenderWindow& window, float deltaTime);
void FillWeapon(Weapon* weapon, float bulletSize, float bulletSpeed, float durationBullet, Bullet::BULLET_EFFECT bulletEffect);
void ShootBullet(Weapon* weapon, Arena* arena, sf::Vector2f dir, float velocityFactor = 1);
void CheckBullet(Arena* arena, sf::RenderWindow& window, float deltaTime);