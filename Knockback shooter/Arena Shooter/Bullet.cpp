#include <iostream>
#include "bullet.h"
#include "utility.h"



// --- Met à jour les balles --- //
void UpdateBullet(Weapon* weapon, Arena* arena, sf::RenderWindow& window, float deltaTime)
{
    MoveBullet(weapon, arena, window, deltaTime);
    CheckBullet(arena, window, deltaTime);
}

// --- Créer une balle avec damages aléatoires et une taille --- //
Bullet* InstantiateBullet(int damage, float bulletSize, float bulletSpeed, float durationBullet, Bullet::BULLET_EFFECT bulletEffect)
{

	Bullet* bullet = new Bullet(damage, bulletSize, bulletSpeed, durationBullet, bulletEffect);
	bullet->currVelocity = sf::Vector2f(0.f, 0.f);
    bullet->bulletDamage = damage;
    bullet->bulletEnd = durationBullet;

    if (bulletEffect == Bullet::BULLET_EFFECT::Normal) 
    { bullet->bulletShape.setFillColor(sf::Color::Blue); }
    if (bulletEffect == Bullet::BULLET_EFFECT::Stun) 
    { bullet->bulletShape.setFillColor(sf::Color::Cyan); }
    if (bulletEffect == Bullet::BULLET_EFFECT::Enrage)
    { bullet->bulletShape.setFillColor(sf::Color::Red); }

    if (bulletEffect == Bullet::BULLET_EFFECT::Confuse)
    {
        bullet->bulletShape.setFillColor(sf::Color::Magenta);
        bullet->bulletShape.setPointCount(8);
    }
    if (bulletEffect == Bullet::BULLET_EFFECT::Burn) 
    {
        bullet->bulletShape.setFillColor(sf::Color(245, 182, 46));
        bullet->bulletShape.setPointCount(6);
    }

	return bullet;
}

// --- Tire les balles --- //
void ShootBullet(Weapon* weapon, Arena* arena, sf::Vector2f dir, float velocityFactor) 
{
    if (!weapon->chamber.empty()) 
    {
        Bullet* bullToShoot = *weapon->chamber.begin();
        cout << weapon->chamber.size() << endl;
        bullToShoot->bulletShape.setPosition(arena->player->currentWeapon->weaponShape.getPosition().x, arena->player->currentWeapon->weaponShape.getPosition().y);
        bullToShoot->currVelocity = dir * bullToShoot->maxSpeed * velocityFactor;
        arena->bulletList.push_back(bullToShoot);
        weapon->chamber.erase(weapon->chamber.begin());
    }
}

// --- Rempli l'arme suivant le nombre maximum de munitions quelle peut contenir --- //
void FillWeapon(Weapon* weapon, float bulletSize, float bulletSpeed, float durationBullet, Bullet::BULLET_EFFECT bulletEffect) 
{
    for (int i = 0; i < weapon->maxAmmo; i++)
    {
        cout << " Adding bullet" << endl;
        weapon->chamber.push_back(InstantiateBullet(weapon->damage, bulletSize, bulletSpeed, durationBullet, bulletEffect));
    }
}

// --- Met à jour les balles --- //
void MoveBullet(Weapon* weapon, Arena* arena, sf::RenderWindow& window, float deltaTime) 
{
    if (!arena->bulletList.empty())
    {
        for (int i = 0; i < arena->bulletList.size(); i++)
        {
            arena->bulletList[i]->bulletShape.move(arena->bulletList[i]->currVelocity * deltaTime);
            window.draw(arena->bulletList[i]->bulletShape);
        }
    }
}

void CheckBullet(Arena* arena, sf::RenderWindow& window, float deltaTime) 
{
    for (int i = 0; i < arena->bulletList.size(); i++)
    {
        if (arena->bulletList[i]->bulletEnd > 0) 
        {
            arena->bulletList[i]->bulletEnd -= deltaTime;
        }
        else 
        {
            arena->bulletList.erase(arena->bulletList.begin() + i);
        }
    }
}
