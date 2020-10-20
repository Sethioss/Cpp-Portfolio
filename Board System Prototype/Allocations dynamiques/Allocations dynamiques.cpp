// Allocations dynamiques.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "board.h"
#include "game.h"

int main()
{
    // Initialise everything below
    sf::RenderWindow newWindow(sf::VideoMode(800, 600), "ChronoSpacer");
    sf::Clock clock;

    Game* createdGame = CreateGame();

    /*ALL PREVIOUS VARIABLES

    //Board* createdBoard = CreateBoard(16, 12, 0, 0);
    //Pawn* createdPawn = CreatePawn(createdBoard->size[0] / 2, createdBoard->size[1] / 2, createdBoard, Pawn::state::PLAYER);
    //Pawn* ennnemyPawn = CreatePawn(createdBoard->size[0] / 2 + 1, createdBoard->size[1] / 2 - 1, createdBoard, Pawn::state::ENEMY);

    */
   
    // Game loop

    while (newWindow.isOpen()) {
        sf::Event event; 
        float deltaTime = clock.restart().asSeconds();

        while (newWindow.pollEvent(event)) {

            //Process any input event here

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    PerformAction(createdGame, UP);
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    PerformAction(createdGame, RIGHT);
                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    PerformAction(createdGame, DOWN);
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    PerformAction(createdGame, LEFT);
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    PerformAction(createdGame, SPACE);
                }
            }

            if (event.type == sf::Event::Closed) {
                newWindow.close();
            }
        }

        UpdateGame(createdGame, deltaTime);
        newWindow.clear();
        // Whatever I want to draw goes here
        
        //std::cout << deltaTime << std::endl;
        DisplayGame(&newWindow, createdGame);

        //DisplayBoard(&newWindow, createdBoard);

        newWindow.display();

        //DestroyBoard(createdBoard);
    }
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
