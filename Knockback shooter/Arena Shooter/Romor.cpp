#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include <math.h>
#include "player.h"
#include "enemy.h"
#include "arena.h"
#include "display.h"
#include "Weapons.h"

using namespace std;

void ArenaShooterv2()
{
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arena Shooter");

    // ---- Initialise everything below ---- //

    Player* Roger = CreatePlayer("Roger", 100, 100, 2.5);
    Arena* battleArena = CreateArena(Roger, window);
    Enemy* enemy1 = CreateEnemy(100, 5, 2, Roger, battleArena);
    Enemy* enemy2 = CreateEnemy(100, 5, 2, Roger, battleArena);
    Enemy* enemy3 = CreateEnemy(100, 5, 2, Roger, battleArena);
    enemy2->enemyShape.setPosition(sf::Vector2f(150, 150));
    enemy3->enemyShape.setPosition(sf::Vector2f(250, 250));
    Weapon* weapon = InstantiateWeapon();

    for (int i = 0; i < battleArena->enemyList.size(); i++)
    {
        cout << "Added Enemy" << endl;
    }
    
    //Weapon* Gun = CreateWeapon("Gun", 24, 20, 120, 5, 3);
    DisplayInfo(Roger);

    // --- Game loop --- //
    while (window.isOpen()) {
        float deltaTime;
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            // --- Process any input event here --- //
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        UpdatePlayer(Roger, battleArena, window, deltaTime);
        UpdateEnemy(enemy1, Roger, battleArena, window, deltaTime);
        UpdateEnemy(enemy2, Roger, battleArena, window, deltaTime);
        UpdateEnemy(enemy3, Roger, battleArena, window, deltaTime);
        UpdateBullet(Roger->currentWeapon, battleArena, window, deltaTime);

        
        

        window.clear();

        // ---- Whatever I want to draw goes here ---- //

        window.draw(Roger->playerShape);
        window.draw(battleArena->wallTop);
        window.draw(battleArena->wallLeft);
        window.draw(battleArena->wallRight);
        window.draw(battleArena->wallBot);
        window.draw(weapon->weaponShape);
        window.draw(enemy1->enemyShape);
        window.draw(enemy2->enemyShape);
        window.draw(enemy3->enemyShape);

        
        //DisplayBullet(battleArena, window);


        window.display();
    }



   
}