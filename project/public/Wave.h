#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "player.h"
#include "Bullet.h"
class Wave
{
public:
	Wave(std::vector<enemy>* allEnemys, sf::FloatRect view, std::vector<Bullet>* bulletList);
	bool EnemyMove();
private:
	std::vector<enemy>* enemyList;
	sf::FloatRect viewRect;
	bool direction;
	float speed = 0.5;
	int enemyStep;
	sf::Clock delayBullet;
	std::vector<Bullet>* bullets;
};

