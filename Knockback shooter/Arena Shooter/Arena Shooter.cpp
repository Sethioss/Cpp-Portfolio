// Arena Shooter.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include <math.h>
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "display.h"
#include "utility.h"

using namespace std;

void ArenaShooter();

int main()
{

    // Cf : Fonction ArenaShooter
    ArenaShooter();
}

void ArenaShooter()
{
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Arena Shooter");
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arena Shooter"  , sf::Style::Fullscreen);


    // ---- Initialise everything below ---- //
    Game* game = CreateGame(window, 4);

    sf::Texture background;
    background.loadFromFile(getAssetsPath(getAppPath().append("Assets\\BackgroundBrick.jpg")));

    sf::Sprite Background(background);

    //sf::Texture wall;
    //wall.loadFromFile(getAssetsPath(getAppPath().append("Assets\\BackgroundWood.jpg")));
    //wall.setRepeated(true);

    //sf::Sprite Wall(wall);
    //Wall.setScale(1, 0.2);

    ///*game->arena->wallTop.setTexture(&wall, true);
    //game->arena->wallTop.setTextureRect(sf::IntRect(0, 0, 400, 400));*/

    sf::Music music;
    music.openFromFile(getAssetsPath(getAppPath().append("Assets\\birthOfAWish.wav")));
    music.setVolume(25.f);
    music.play();

    sf::SoundBuffer buffer;
    sf::Sound sound;

    sf::Clock clock;
    float deltaTime;
    deltaTime = clock.restart().asSeconds();

    // --- Game loop --- //
    while (window.isOpen()) {

        // --- gameOver = true QUAND le joueur appuie sur Espace --- //
        while (game->gameOver != true)
        {

            deltaTime = clock.restart().asSeconds();

            sf::Event event;
            while (window.pollEvent(event)) {
                // --- Process any input event here --- //

                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
            }

            // --- All Updates goes here --- //

            Background.setOrigin(Background.getTexture()->getSize().x / 2, Background.getTexture()->getSize().y / 2);
            Background.setPosition(1920 / 2, 1080 / 2);
            //Background.rotate(100);

            UpdateGame(window, game, deltaTime);
            UpdateAudio(game, &buffer, &sound);


            window.clear();

            // ---- Whatever I want to draw goes here ---- //
            window.draw(Background);
           // window.draw(Wall);
            DisplayGame(game, window);


            window.display();
        }

        game = Reload(game, window, deltaTime);
    }
}