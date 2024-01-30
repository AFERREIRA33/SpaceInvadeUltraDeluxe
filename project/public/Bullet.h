#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"
class Bullet
{
public:
	Bullet(sf::Vector2f playerPos, std::vector<enemy>* allEnemys, bool player);
	~Bullet();
	sf::RectangleShape theBullet;
	bool shot(sf::RenderWindow* window, sf::Sprite player);
	bool isPlayer;
private:
	std::vector<enemy>* enemyList;
	sf::Vector2f origin;
	sf::Vector2f direction;
};

