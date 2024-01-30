#include "Wave.h"
#include <iostream>
Wave::Wave(std::vector<enemy>* allEnemys, sf::FloatRect view, std::vector<Bullet>* bulletList) {
	enemyList = allEnemys;
	viewRect = view;
	direction = true;
	enemyStep = enemyList->size() - 5;
	delayBullet.getElapsedTime();
	bullets = bulletList;
}

// gestion des différentes actions des ennemis
// Retourne un boolean pour la gestion de la défaite si les ennemis sont trop bas
bool Wave::EnemyMove() {
	bool touch = false;

	// Accélération des ennemis selon le nombre d'ennemis restant
	if (enemyList->size() <= enemyStep) {
		speed += 0.5;
		if (enemyStep > 0) {
			enemyStep -= 5;
		}
		else {
			enemyStep = 0;
		}
	}
	// Verifie si un ennemi touche le bord de l'écran
	// Si oui inverse la direction
	for (int i = 0; i < enemyList->size(); i++) {
		if (!viewRect.contains((*enemyList)[i].invader.getPosition().x, (*enemyList)[i].invader.getPosition().y) || !viewRect.contains((*enemyList)[i].invader.getPosition().x+24, (*enemyList)[i].invader.getPosition().y)) {
			touch = true;
			break;
		}
	}
	if (touch) {
		direction = !direction;
	}

	// Fait tirer un ennemi aléatoire qui est le plus bas de sa colonne exemple (les "1" peuvent tirer):
	/*
	0 0 0 0 1 0 1
	1 0 1 0   0  
	  1   1   1
	*/
	int hit = std::rand() % enemyList->size();
	sf::Vector2f posHit = (*enemyList)[hit].invader.getPosition();
	for (int i = 0; i < enemyList->size(); i++) {
		if ((*enemyList)[i].invader.getPosition().x == posHit.x && (*enemyList)[i].invader.getPosition().y > posHit.y) {
			hit = i;
		}
		if (touch){
			(*enemyList)[i].invader.move(0, 5);
		}
		if (direction) {
			(*enemyList)[i].invader.move(-speed, 0);
		}
		else {
			(*enemyList)[i].invader.move(speed, 0);
		}
	}
	// Vérifie si la ligne la plus basse d'ennemis est au desus de la limite et renvoie false si ils sont trop bas
	if (enemyList->back().invader.getPosition().y >= viewRect.height - enemyList->back().invader.getGlobalBounds().height * 3) {
		return false;
	}

	// Tire des ennemis gérer par un timer
	if (delayBullet.getElapsedTime().asSeconds() > 0.5) {
		Bullet bullet((*enemyList)[hit].invader.getPosition(), enemyList, false);
		bullets->push_back(bullet);
		delayBullet.restart();
	}
	return true;

}