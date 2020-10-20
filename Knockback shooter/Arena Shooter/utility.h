#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include "player.h"

using namespace std;

float dot(const sf::Vector2f& lv, const sf::Vector2f& rv);
sf::Vector2f normalise(sf::Vector2f source);
string getAppPath();
string getAssetsPath(string appPath);
sf::Vector2f GetPlayerCenter(Player* player);
sf::Vector2f GetAimDirNorm(Player* player, sf::RenderWindow& window);
int Random(int random);
void UpdateRandom();
float easeOutQuint(float curTime, float startValue, float changeInValue, float duration);
