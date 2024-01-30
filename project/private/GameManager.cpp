#include "GameManager.h"

// Constructeur
GameManager::GameManager(int sx,int sy) :
     ScreenX(sx), ScreenY(sy)
{
    score = 0;
}

// Fonction qui g�re la boucle de jeu
void GameManager::Gameplay() {
    enemys.clear();
    sf::RenderWindow window(sf::VideoMode(ScreenX, ScreenY), "My window");
    window.setFramerateLimit(60);
    score = 0;
    int life = 3;
    bool pause = false;
    bool firstTick = true;

    sf::View view = window.getView();
    sf::FloatRect viewRect(view.getCenter() - view.getSize() / 2.f, view.getSize());

    // zone de texte du score
    sf::Text text;
    text.setFont(font);
    text.setString("Score : " + std::to_string(score));
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Zone de text de la vie
    sf::Text lifeText;
    lifeText.setFont(font);
    lifeText.setString("Life : " + std::to_string(life));
    lifeText.setCharacterSize(20);
    lifeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    lifeText.getGlobalBounds().width;
    lifeText.setPosition(view.getSize().x- 70, lifeText.getPosition().y);
    std::vector<Bullet> bullets;

    // Texte du menu pause
    sf::Text resume;
    resume.setFont(font);
    resume.setString("Press P for resume");
    resume.setCharacterSize(30);
    resume.setFillColor(sf::Color::Green);
    sf::Text restart;
    restart.setFont(font);
    restart.setString("Press R for restart");
    restart.setCharacterSize(30);
    resume.setFillColor(sf::Color::Green);

    // Chargement des textures de l'ennemies
    sf::Texture textureEnemy;
    if (!textureEnemy.loadFromFile("rsc/sprites/closed.png"))
        std::cout << "image not load";
    sf::Sprite aEnemy(textureEnemy);

    // Cr�ation des lignes d'ennemies chaque est ennemie est un objet de classe "invader" 
    // Ils sont �galement stocker dans un vector du nom de "enemys"
    for (size_t i = 0; i < 33; i++)
    {
        enemy invader(aEnemy);
        if (i < 11) {
            invader.invader.setPosition(invader.invader.getPosition().x + 30 * i, invader.invader.getPosition().y+ 20);
        }
        else if (i < 22) {
            invader.invader.setPosition(invader.invader.getPosition().x + 30 * (i - 11), invader.invader.getPosition().y + 30+20);
        }
        else {
            invader.invader.setPosition(invader.invader.getPosition().x + 30 * (i - 22), invader.invader.getPosition().y + 60+20);
        }
        enemys.push_back(invader);
    }

    // Chargement texture du joueur
    sf::Texture texture;
    if (!texture.loadFromFile("rsc/sprites/mec_qui_tire.png"))
        std::cout << "image not load";
    Player player(view, texture, &bullets, &enemys);

    // Cr�ation de la classe g�rant le d�placement des ennemis et leurs tires
    Wave wave(&enemys, viewRect, &bullets);

    // Chargement du fichier pour la police d'�criture
    if (!font.loadFromFile("./arial.ttf"))
        std::cout << "fnt not found";

    // Boucle de jeu  pour la gestion des diff�rents �v�nements
    while (window.isOpen())
    {
        // Gestion des diff�rentes touches d�clenchant des �v�nement
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased) {
                // gestion des evenement li� au menu pause
                if (event.key.code == sf::Keyboard::P)
                {
                    pause = !pause;
                    firstTick = true;
                }
                if (event.key.code == sf::Keyboard::R && pause)
                {
                    // Recharge L'�cran de d�marrage
                    window.close();
                    StartScreen();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
            {
                window.close();
            }
            //Gestion des evenment li� au joueur
            player.Action();
        }

        // Verification pour le menu pause et pour bloquer le reste du jeu
        if (pause && firstTick) {
            resume.setPosition(view.getCenter().x - resume.getGlobalBounds().width / 2, ScreenY - resume.getGlobalBounds().height * 2);
            window.draw(resume);
            restart.setPosition(view.getCenter().x - restart.getGlobalBounds().width / 2, ScreenY - restart.getGlobalBounds().height * 4);
            window.draw(restart);
            window.display();
            firstTick = false;
        }
        else if (!pause) {
            window.clear(sf::Color::Black);

            //G�n�ration du joueur
            window.draw(player.line);

            // Verification des diff�rentes conditions de victoire et de d�faite ( plus de vie, ennemis trop bas, plus d'ennemis)
            // Et gestion des d�placements des ennemis
            if (life < 1) {
                window.close();
                EndScreen(false);
            }
            else if (enemys.size() > 0) {
                if (wave.EnemyMove()) {
                    for (size_t i = 0; i < enemys.size(); i++)
                    {
                        window.draw(enemys[i].invader);
                    }
                }
                else {
                    window.close();
                    EndScreen(false);
                }
            }
            else {
                score = score * life;
                window.close();
                EndScreen(true);
            }

            // Gestion des �v�nement concernant les balles (touche un ennemi, sort de l'�cran, touche un joueur)
            for (size_t i = 0; i < bullets.size(); i++)
            {
                if (bullets[i].shot(&window, player.line)) {
                    if (bullets[i].isPlayer) {
                        score += 10;
                        text.setString("Score :" + std::to_string(score));
                    }
                    else {
                        if (life > 0)
                            life--;
                        lifeText.setString("Life : " + std::to_string(life));
                    }
                    bullets.erase(std::next(bullets.begin(), i));
                }
                else if (!viewRect.contains(bullets[i].theBullet.getPosition())) {
                    bullets.erase(std::next(bullets.begin(), i));
                }
            }

            //dessine les diff�rentes zone de texte
            window.draw(lifeText);
            window.draw(text);

            window.display();
        }
    }
}

// Foonction G�n�rant la fen�tre du d�marrage du jeu
void GameManager::StartScreen() {
    sf::RenderWindow window(sf::VideoMode(ScreenX, ScreenY), "My window");
    window.setFramerateLimit(60);
    sf::View view = window.getView();
    sf::FloatRect viewRect(view.getCenter() - view.getSize() / 2.f, view.getSize());

    // Titre du jeu
    sf::Text title;
    title.setFont(font);
    title.setString("Space Invader ULTRA DELUXE");
    title.setCharacterSize(20);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setFillColor(sf::Color::Green);
    std::cout << title.getGlobalBounds().height << std::endl;

    // Affihage des touches et de leurs utilit�es
    sf::RectangleShape key;
    sf::Text keyText;
    keyText.setFont(font);
    keyText.setCharacterSize(15);
    keyText.setFillColor(sf::Color::Black);
    sf::Text usage;
    usage.setFont(font);
    usage.setCharacterSize(15);
    usage.setFillColor(sf::Color::Green);

    // Texte indiquant quelle touche appuyer pour lancer
    sf::Text play;
    play.setFont(font);
    play.setString("PRESS SPACE");
    play.setCharacterSize(30);
    play.setFillColor(sf::Color::Green);
    if (!font.loadFromFile("./arial.ttf"))
        std::cout << "fnt not found";

    // Timer permettant de faaire clignoter le texte
    sf::Clock delayText;
    delayText.getElapsedTime();
    bool isVisible = true;

    // Cr�ation de la fen�tre
    while (window.isOpen())
    {
        // Gestion des �v�nements en rapport avec des touches ou d�finis par sfml
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
            {
                window.close();
                Gameplay();
            }
        }
        window.clear(sf::Color::Black);

        // Desine le titre
        title.setPosition(view.getCenter().x - (title.getGlobalBounds().width / 2), title.getPosition().y);
        window.draw(title);

        // Dessie les touches de d�placements
        key.setSize(sf::Vector2f(40, 40));
        key.setPosition(title.getPosition().x, title.getPosition().y + 50);
        window.draw(key);
        keyText.setString("Q, K");
        keyText.setPosition(key.getPosition().x + key.getGlobalBounds().width / 2 - keyText.getGlobalBounds().width / 2, key.getPosition().y + key.getGlobalBounds().height / 2 - keyText.getGlobalBounds().height/2);
        window.draw(keyText);
        key.setPosition(key.getPosition().x + key.getGlobalBounds().width +5, key.getPosition().y);
        window.draw(key);
        keyText.setString("D, M");
        keyText.setPosition(key.getPosition().x + key.getGlobalBounds().width / 2 - keyText.getGlobalBounds().width / 2, key.getPosition().y + key.getGlobalBounds().height / 2 - keyText.getGlobalBounds().height / 2);
        window.draw(keyText);
        usage.setPosition(key.getPosition().x + key.getGlobalBounds().width + 5, keyText.getPosition().y);
        usage.setString("Player movement");
        window.draw(usage);

        // Dessine la touches de tire
        key.setSize(sf::Vector2f(85, 40));
        key.setPosition(title.getPosition().x, title.getPosition().y + 150);
        window.draw(key);
        keyText.setString("Space");
        keyText.setPosition(key.getPosition().x + key.getGlobalBounds().width / 2 - keyText.getGlobalBounds().width / 2, key.getPosition().y + key.getGlobalBounds().height / 2 - keyText.getGlobalBounds().height / 2);
        window.draw(keyText);
        usage.setPosition(usage.getPosition().x, keyText.getPosition().y);
        usage.setString("Shoot");
        window.draw(usage);

        // Dessine la touche de pause
        key.setPosition(key.getPosition().x + key.getGlobalBounds().height / 2 , title.getPosition().y + 100);
        key.setSize(sf::Vector2f(40, 40));
        window.draw(key);
        keyText.setString("P");
        keyText.setPosition(key.getPosition().x + key.getGlobalBounds().width / 2 - keyText.getGlobalBounds().width / 2, key.getPosition().y + key.getGlobalBounds().height / 2 - keyText.getGlobalBounds().height / 2);
        window.draw(keyText);
        usage.setPosition(usage.getPosition().x, keyText.getPosition().y);
        usage.setString("Pause");
        window.draw(usage);
        // D�lai pour faire clignoter le texte
        if (delayText.getElapsedTime().asSeconds() > 0.5) {
            isVisible = !isVisible;
            delayText.restart();
        }
        if (isVisible) {
            play.setPosition(view.getCenter().x - play.getGlobalBounds().width / 2, ScreenY - play.getGlobalBounds().height * 2);
            window.draw(play);
        }

        window.display();
    }
}

// Fonction g�n�rant l'�cran de fin du jeu
// Elle re�oit dun boolean pour savoir si le joueur � gagn� ou perdu
void GameManager::EndScreen(bool win) {
    sf::RenderWindow window(sf::VideoMode(ScreenX, ScreenY), "My window");
    window.setFramerateLimit(60);
    sf::View view = window.getView();
    sf::FloatRect viewRect(view.getCenter() - view.getSize() / 2.f, view.getSize());

    // Cr�ation du texte montrant si le joueur � gagner ou perdu
    sf::Text text;
    text.setFont(font);
    if(win)
        text.setString("You win !");
    else
        text.setString("You lose");
    text.setCharacterSize(40);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(view.getCenter().x - (text.getGlobalBounds().width / 2), text.getPosition().y );
    
    // Cr�ation du texte affichant le score du joueur � la fin de sa partie
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score : " + std::to_string(score));
    scoreText.setCharacterSize(40);
    scoreText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    scoreText.setPosition(view.getCenter().x - (scoreText.getGlobalBounds().width / 2), scoreText.getPosition().y + text.getGlobalBounds().height +5);

    // Cr�ation du texte indiquannt quelle touche appuyer pour relancer
    sf::Text play;
    play.setFont(font);
    play.setString("PRESS R FOR RESTART");
    play.setCharacterSize(30);
    play.setFillColor(sf::Color::Green);
    if (!font.loadFromFile("./arial.ttf"))
        std::cout << "fnt not found";

    // Cr�ation/lancement d'un timer pour faire clignoter le texte
    sf::Clock delayText;
    delayText.getElapsedTime();
    bool isVisible = true;

    // G�n�ration de la fen�tre
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        // Gestion des �v�nements en rapport avec des touches ou d�finis par sfml
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                window.close();
                StartScreen();
            }

        }
        // Affichage des dif�rents textes � afficher
        window.draw(text);
        window.draw(scoreText);
        if (delayText.getElapsedTime().asSeconds() > 0.5) {
            isVisible = !isVisible;
            delayText.restart();
        }
        if (isVisible) {
            play.setPosition(view.getCenter().x - play.getGlobalBounds().width / 2, ScreenY - play.getGlobalBounds().height * 2);
            window.draw(play);
        }
        window.display();
    }
}