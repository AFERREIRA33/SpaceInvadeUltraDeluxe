#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include "enemy.h"
class Player
{
public:
	Player(const sf::View& view, const sf::Texture& texture, std::vector<Bullet>* bulletList, std::vector<enemy>* allEnemys);
	~Player();
	sf::Sprite line;
	void Action();
private:
	std::vector<Bullet>* bullets;
	std::vector<enemy>* enemyList;
	sf::Clock delayBullet;
	sf::View viewW;
};

