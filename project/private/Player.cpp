#include "Player.h"
#include <iostream>

Player::Player(const sf::View& view, const sf::Texture& texture, std::vector<Bullet>* bulletList, std::vector<enemy>* allEnemys) :
    bullets(bulletList)
{
	viewW = view;
    enemyList = allEnemys;
    line.setTexture(texture, true);
    line.setPosition(viewW.getCenter().x, viewW.getSize().y - 40);
    delayBullet.getElapsedTime();
}
Player::~Player() {
}

// Gestion des actions du joueur
void Player::Action() {
    sf::FloatRect viewRect(viewW.getCenter() - viewW.getSize() / 2.f, viewW.getSize());

    // Gestion du tir avec un délai pour viter les tirs en raffale
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (delayBullet.getElapsedTime().asSeconds() > 0.5) {
            Bullet bullet(line.getPosition(), enemyList, true);
            bullets->push_back(bullet);
            delayBullet.restart();
        }
    }

    // Déplacement du joueur
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && viewRect.contains(line.getPosition().x - 5, line.getPosition().y)) {
        line.move(-2, 0);
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::M) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && viewRect.contains(line.getPosition().x + 31, line.getPosition().y)) {
        line.move(2, 0);
    }
}