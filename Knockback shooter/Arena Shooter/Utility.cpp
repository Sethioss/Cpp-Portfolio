#include <iostream>
#include "utility.h"

// --- Calcule la distance entre deux vecteurs --- //
float dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
{
	return lv.x * rv.x + lv.y * rv.y;
}

// --- Normalise le vecteur --- //
sf::Vector2f normalise(sf::Vector2f source)
{
	float length = std::sqrt(dot(source, source));
	if (length != 0) source /= length;
	return source;
}

// --- Trouve dans quel dossier est l'application --- //
string getAppPath()
{
	char cExeFilePath[256];
	GetModuleFileNameA(NULL, cExeFilePath, 256);
	std::string exeFilePath = cExeFilePath;
	int exeNamePos = exeFilePath.find_last_of("\\/");
	std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
	return appPath;
}

// --- Trouve l'Asset --- //
string getAssetsPath(string appPath)
{
	string assetPath = appPath.append(""); // ajoute "Assets" à la fin du string assetPath grace à append 
	return assetPath;
}

// --- Trouve le centre du Joueur --- //
sf::Vector2f GetPlayerCenter(Player* player)
{
	sf::Vector2f centerPos;
	centerPos = sf::Vector2f(player->playerShape.getPosition().x + player->playerShape.getRadius(), player->playerShape.getPosition().y + player->playerShape.getRadius());
	return centerPos;
}

// --- Normalise l'aim du Joueur --- //
sf::Vector2f GetAimDirNorm(Player* player, sf::RenderWindow& window)
{
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	playerCenter = sf::Vector2f(player->playerShape.getPosition().x + player->playerShape.getRadius(), player->playerShape.getPosition().y + player->playerShape.getRadius());
	mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
	aimDir = mousePosWindow - playerCenter;
	aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

	return aimDirNorm;
}

// --- Tire un chiffre / nombre aléatoire --- //
int Random(int toRandom)
{
	int sortedNumber = rand() % (toRandom + 1);

	cout << "the sorted is : " << sortedNumber << endl;

	return sortedNumber;
}

// --- Met à jour le Random --- //
void UpdateRandom() 
{
	srand(time(NULL)); 
}

float easeOutQuint(float curTime, float startValue, float changeInValue, float duration)
{
	curTime /= duration;
	curTime--;
	return changeInValue * (curTime * curTime * curTime * curTime * curTime + 1) + startValue;
};