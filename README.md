# Projet C - Platform 2D

Jeu de plateforme 2D écrit en C avec la bibliothèque SDL 1.2, inspiré de titres comme Mario ou Hollow Knight.
Projet final du cours de Langage C (ESGI, 2e année, 2026-2027).

## Le jeu

- Déplacement du joueur (course, saut, collisions)
- Ennemis et combat
- Menu interactif : sélection et personnalisation du personnage avant de lancer la partie
- Éditeur de cartes
- Système de plugins (extensions chargées par le jeu)

## Répartition des tâches

Pour garantir un travail équitable, la charge de chaque tâche est estimée en points de difficulté (1 = simple, 6 = gros morceau).

| Membre | Tâches | Charge estimée |
| --- | --- | --- |
| Gaël | **Moteur et joueur**<br>Boucle de jeu et gestion du temps (2)<br>Physique : gravité, saut, collisions avec la carte (5)<br>Caméra qui suit le joueur (2)<br>Affichage de la carte (2)<br>Joueur : contrôles et états courir / sauter / tomber (3)<br>Affichage des PV à l'écran (1) | 15 pts |
| Farmata | **Entités et combat**<br>Module commun de sprites et animations (3)<br>Combat : zones de coups, points de vie, dégâts, invincibilité (4)<br>IA des ennemis : patrouille, détection, poursuite (4)<br>Objets à ramasser, victoire et défaite (2)<br>Sélection et personnalisation du personnage (3) | 16 pts |
| Calvin | **Outils et interface**<br>Format des niveaux, chargement et sauvegarde (3)<br>Éditeur de cartes (6)<br>Système de plugins avec 1 ou 2 plugins d'exemple (4)<br>Menus principal et pause (2) | 15 pts |

Notes :

- La répartition s'applique au travail restant après le prototype du 18/11/2026 ; le code déjà écrit reste attribué à son auteur.
- Les structures partagées (`Entity`, `Level`) et les fonctions appelées entre modules sont définies en commun.
- La répartition est revue chaque semaine et ajustée si une tâche s'avère plus longue que prévu.

## Échéances

| Étape | Date |
| --- | --- |
| Prototype | mercredi 18/11/2026, 23h59 |
| Rendu final | mercredi 09/12/2026, 23h59 |
| Soutenance (15 min, 5 min chacun) | 10/12/2026 |

## Installation

Sous Linux (Debian / Ubuntu) : si besoin

```bash
sudo apt install build-essential libsdl1.2-dev
git clone https://github.com/gfadeyi/projet-c-platform-2d.git
cd projet-c-platform-2d
```

## Compilation

Le Makefile arrivera avec les premiers fichiers source. La commande de base :

```bash
gcc -Wall -Wextra src/*.c -o platformer $(sdl-config --cflags --libs)
./platformer
```

## Organisation du dépôt (prévue)

| Dossier | Contenu |
| --- | --- |
| `src/` | Code source (`.c`) |
| `include/` | En-têtes (`.h`) |
| `assets/` | Images, sons, polices |
| `maps/` | Cartes créées avec l'éditeur |
| `plugins/` | Extensions du jeu |
| `docs/` | Roadmap et documents du projet |

## Travailler à trois

- `main` doit toujours compiler : on ne pousse pas directement dessus
- Une branche par tâche : `feature/saut-joueur`, `fix/collision-sol`
- Une pull request relue par au moins un autre membre avant la fusion
- Des commits courts avec un message clair : `Ajouter le saut du joueur`
- Chacun doit pouvoir expliquer le code dont il est l'auteur le jour de la soutenance

```bash
git checkout main
git pull
git checkout -b feature/ma-fonctionnalite
# ... coder, tester ...
git add .
git commit -m "Ajouter le saut du joueur"
git push -u origin feature/ma-fonctionnalite
```
