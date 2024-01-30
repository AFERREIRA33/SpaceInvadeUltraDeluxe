#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Bullet.h"
#include "enemy.h"
#include "Wave.h"

class GameManager
{
public:
	GameManager(int sx, int sy);
	void StartScreen();
	void Gameplay();
	void EndScreen(bool win);
private:
	std::vector<enemy> enemys;
	sf::Font font;
	sf::Text text;
	int score;
	const int ScreenX;
	const int ScreenY;
};

