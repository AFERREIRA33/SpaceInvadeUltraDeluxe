# Space Invader Ultra Deluxe

## Concepte

Des aliennes descendent en ligne pour se rapprocher du joueur et le joueur doit leur tirer dessus.

## Scénario

Tu es un vaiseau spatial protégeant la terre d'une invasion alienne.

## Mécanique

- Le joueur peut tirer et se déplacer de droite à gauche en esquivant les balles ennemis et doit empêcher les ennemis d'arriver en bas
- Un ennemi tire toutes les 0.5 secondes , il est choisi aléatoirement parmis tous les aliennes les plus bas de leur colonne respectif
- Le score est calculé avec 2 facteurs :
    - le nombre d'ennemis éliminés
    - le nombre de vie restante

## Style

Les sprites viennent du jeu "space invader" de la ATARI car mon jeu est inspiré de celui ci.

## Condition de victoire/défaite

- Objectifs:
    - Eliminer tous les aliennes
    - perdre le moins de vie pour le score
- Condition de défaite:
    - Perdre toutes ses vies
    - Les ennemis atteignent la Terre (le bas de l'écran)

## Controle

- Menu de démarrage :
    - Espace : Lance la partie
- Jeux : 
    - Espace : Tir
    - Q, K : Déplacement du joueur à gauche
    - D, M : Déplacement du joueur à droite
    - P : Pause
- Jeux en pause :
    - P : relance le temps
    - R : Redémarre le jeu
- Ecran de fin :
    - R : Redémarre le jeu


