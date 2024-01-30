#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f playerPos, std::vector<enemy>* allEnemys, bool player) {
	origin = playerPos;
	enemyList = allEnemys;
	theBullet.setSize(sf::Vector2f(5, 10));
	theBullet.setPosition(playerPos.x + 10, playerPos.y - 5);
	isPlayer = player;
}
Bullet::~Bullet() {

}

// Fonction gérant le déplacement des balles et les evenements 
bool Bullet::shot(sf::RenderWindow *window, sf::Sprite player) {
	// Vérifie à qui appartient la balle
	if (isPlayer) {
		this->theBullet.move(0, -5);
		for (size_t i = 0; i < enemyList->size(); i++)
		{
			// Vérifie si la balle touches un ennemi
			if (theBullet.getGlobalBounds().intersects((*enemyList)[i].invader.getGlobalBounds())) {
				enemyList->erase(std::next(enemyList->begin(), i));
				return true;
			}
		}
	}
	else {
		this->theBullet.move(0, 5);
		//  Vérifie si la balles touches le joueur
		if (theBullet.getGlobalBounds().intersects(player.getGlobalBounds())) {
			std::cout << "hit" << std::endl;
			return true;
		}
	}
	window->draw(this->theBullet);
	return false;
}