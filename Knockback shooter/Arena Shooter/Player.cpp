#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "utility.h"
#include "player.h"
#include "enemy.h"
#include "Weapons.h"
#include "arena.h"

const float PI = 3.14159265;

using namespace std;

// --- Créer le joueur --- //
Player* CreatePlayer(string name, int health, float speed) 
{
    Player* createPlayer = new Player(name, health, speed);

    createPlayer->minSpeed = 170;
    createPlayer->maxSpeed = 280;
    createPlayer->speedMove = createPlayer->minSpeed;

    createPlayer->playerShape.setRadius(40);
    createPlayer->playerShape.setOrigin(createPlayer->playerShape.getRadius(), createPlayer->playerShape.getRadius());

    createPlayer->playerShape.setPosition(400, 400);

    createPlayer->playerShape.setFillColor(sf::Color::Yellow);
    createPlayer->currentWeapon = InstantiateWeapon();

    // --- Définir les paramètres de centre et de position de l'arme --- //
    createPlayer->currentWeapon->weaponShape.setPosition(createPlayer->playerShape.getPosition().x, createPlayer->playerShape.getPosition().y + createPlayer->playerShape.getRadius());

    return createPlayer;
}

// --- Affiche les informations du joueur --- //
void DisplayInfo(Player* player) 
{
	cout << "Nom : " << player->name << " Vie : " << player->health << " Speed : " << player->speedMove << endl;
}

// --- Met à jour les informations et inputs du joueur --- //
void UpdatePlayer(Player* player, Arena* arena, sf::RenderWindow& window, float deltaTime, Game* game)
{
    Move(player, arena, deltaTime);
    CheckPlayerStates(player, deltaTime);
    Shoot(player, player->currentWeapon, arena, window, deltaTime, game);
    SwapWeapon(arena);
    CheckShoot(arena, player, window, deltaTime);
    LookAtMouse(player, window);
}

// --- Contrôle les états du joueur  --- //
void CheckPlayerStates(Player* player, float deltaTime)
{
    // --- Normalisation du temp (doit être changé) --- //
    float Norm = 80;
    if (player->isInvicible)
    {
        if (player->invincibilityTimer > 0)
        {
            player->invincibilityTimer -= deltaTime;
        }
        else
        {
            player->playerShape.setFillColor(sf::Color::Yellow);
            player->invincibilityTimer = Norm;
            player->isInvicible = false;
        }
    }

    if (!player->isRunning && player->speedMove > player->minSpeed&& player->canMove)
    {
        player->speedMove -= 3.36f;
    }
    else if (player->speedMove < player->minSpeed && player->canMove)
    {
        player->speedMove = player->minSpeed;
    }
}

// --- Contrôle le cooldown de l'arme --- //
void CheckShoot(Arena* arena, Player* player, sf::RenderWindow& window, float deltaTime)
{
    int ammoScale = Random(player->currentWeapon->maxAmmo);

    if (!player->currentWeapon->canShoot)
    {
        if (player->currentWeapon->cooldown > 0)
        {
            player->currentWeapon->cooldown -= deltaTime;
        }
        else
        {
            player->currentWeapon->canShoot = true;
        }
    }
    if (player->currentWeapon->ammo <= ammoScale && !player->newWeaponCreated) 
    {
        GenerateWeaponOnField(arena, window);
        player->newWeaponCreated = true;
    }

    if (player->swapTime > 0) 
    {
        player->swapTime -= deltaTime;
    }
    else 
    {
        player->canSwap = true;
    }
}

// --- Controle les inputs du joueur pour le mouvement --- //
void Move(Player* player, Arena* arena, float deltaTime)
{
    if (player->canMove)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            if (!player->playerShape.getGlobalBounds().intersects(arena->wallTop.getGlobalBounds()))
            {
                player->playerShape.move(0, -player->speedMove * deltaTime);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (!player->playerShape.getGlobalBounds().intersects(arena->wallBot.getGlobalBounds()))
            {
                player->playerShape.move(0, player->speedMove * deltaTime);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            if (!player->playerShape.getGlobalBounds().intersects(arena->wallLeft.getGlobalBounds()))
            {
                player->playerShape.move(-player->speedMove * deltaTime, 0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (!player->playerShape.getGlobalBounds().intersects(arena->wallRight.getGlobalBounds()))
            {
                player->playerShape.move(player->speedMove * deltaTime, 0);
            }
        }

        // ---- Player Run ---- //
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            player->isRunning = true;

            if (player->speedMove < player->maxSpeed && player->isRunning)
            {
                player->speedMove += 1.68f;
            }
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (player->isRunning == true)
            {

                player->isRunning = false;

            }
        }
    }
    else {
        // --- Knockback --- //
        player->playerShape.move(player->knockbackDir * player->speedMove * deltaTime);

        float ease = ((easeOutQuint(deltaTime, player->speedMove, player->speedMove * player->currentWeapon->knockBackSpeed, player->currentWeapon->knockBackSpeed) * 0.01f));

        std::cout << "Ease : " << ease << endl;

        player->speedMove -= player->speedMove * ease * deltaTime;

        if (ease < player->currentWeapon->knockbackDamping)
        {
            player->canMove = true;
        }
    }
}

// --- Controle les inputs du joueur pour le tir --- //
void Shoot(Player* player, Weapon* weapon, Arena* arena, sf::RenderWindow& window, float deltaTime, Game* game) 
{
    sf::Vector2f playerCenter = GetPlayerCenter(player);
    sf::Vector2f aim = GetAimDirNorm(player, window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (weapon->canShoot)
        {
                if(weapon->ammo > 0)
                {
                    game->audioToPlay = weapon->weaponSound;
                    weapon->canShoot = false;
                    cout << "PAN" << endl;
                    
                    // --- PAN goes here --- //

                    if (player->currentWeapon->name == "Shotgun")
                    {
                        float angle = atan2(aim.y, aim.x);

                        for (int i = 0; i < 3; i++)
                        {
                            float deltaAngle = (rand() / (float)RAND_MAX) * (PI / 4);
                            float shotAngle = angle + deltaAngle;

                            float velocityFactor = (rand() / (float)RAND_MAX * 0.4f) + 0.8f;

                            float shotX = cos(shotAngle);
                            float shotY = sin(shotAngle);

                            ShootBullet(weapon, arena, sf::Vector2f(shotX, shotY), velocityFactor);
                            weapon->ammo--;
                        }
                    }
                    else 
                    {
                        ShootBullet(weapon, arena, aim);
                        weapon->ammo--;
                    }

                    weapon->cooldown = weapon->cadency;
                    Knockback(player, window, weapon->knockBackSpeed, deltaTime);
                }
        }
    }
}

void SwapWeapon(Arena* arena) 
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
        if (arena->player->oldWeapon != nullptr && arena->player->canSwap)
        {
            arena->player->canSwap = false;
            Weapon* temp = new Weapon();
            temp = arena->player->currentWeapon;
            arena->player->currentWeapon = arena->player->oldWeapon;
            arena->player->oldWeapon = temp;
            arena->player->swapTime = 0.5f;
        }
    }
}


// --- Contrôle le recul du joueur basé sur le recul de l'arme --- //
void Knockback(Player* player, sf::RenderWindow& window, float knockbackSpeed, float deltaTime)
{
    sf::Vector2f playerCenter = GetPlayerCenter(player);
    sf::Vector2f aim = GetAimDirNorm(player, window);
    player->canMove = false;
    player->knockbackDir = -aim;
    player->speedMove = knockbackSpeed * 1700;
}

// --- Rotate le joueur et l'arme selon l'emplacement de la souris --- //
void LookAtMouse(Player * player, sf::RenderWindow & window)
{
        sf::Vector2f playerPos = GetPlayerCenter(player);
        sf::Vector2f aim = sf::Vector2f(sf::Mouse::getPosition(window));


        float offSetX = aim.x - playerPos.x;
        float offSetY = aim.y - playerPos.y;

        float rotation = atan2(offSetY, offSetX);
        rotation *= 180 / PI;

        float weaponRotation = 2;

        player->playerShape.setRotation(rotation);
        player->currentWeapon->weaponShape.setRotation(rotation + 180);
}