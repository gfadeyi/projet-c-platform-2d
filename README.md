# Projet C - Platform 2D

Jeu de plateforme 2D écrit en C avec la bibliothèque SDL 1.2, inspiré de titres comme Mario ou Hollow Knight.
Projet final du cours de Langage C (ESGI, 2e année, 2026-2027).

## Le jeu

- Déplacement du joueur (course, saut, collisions)
- Ennemis et combat
- Menu interactif : sélection et personnalisation du personnage avant de lancer la partie
- Éditeur de cartes
- Système de plugins (extensions chargées par le jeu)

## Équipe

| Membre | Rôle |
| --- | --- |
| Gael | Moteur physique, rendu, combat |
| Farmata | Gameplay, menus, IA des ennemis |
| Calvin | Fichiers, éditeur de cartes, plugins |

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
