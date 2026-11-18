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

Dépendances : le compilateur `gcc`, l'outil `make` et la bibliothèque SDL 1.2.

### Linux (Debian / Ubuntu)

```bash
sudo apt install build-essential libsdl1.2-dev
git clone https://github.com/gfadeyi/projet-c-platform-2d.git
cd projet-c-platform-2d
```

### Windows (MSYS2 + VS Code)

VS Code est seulement l'éditeur : le compilateur et SDL s'installent à part, avec MSYS2.

1. Installer MSYS2 depuis https://www.msys2.org en gardant le dossier proposé, `C:\msys64`.
   Les réglages VS Code du dépôt (`.vscode/`) utilisent ce chemin.
2. Ouvrir le terminal « MSYS2 UCRT64 » (menu Démarrer) et mettre MSYS2 à jour :

   ```bash
   pacman -Syu
   ```

   Si la fenêtre se ferme, la rouvrir et relancer la même commande.
3. Installer gcc, SDL 1.2, le débogueur gdb et make :

   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-SDL mingw-w64-ucrt-x86_64-gdb make
   ```

4. Dans VS Code, installer l'extension « C/C++ » de Microsoft (`ms-vscode.cpptools`).
5. Cloner le dépôt, puis dans VS Code : Fichier > Ouvrir le dossier > `projet-c-platform-2d`
   (ce dossier précisément, sinon VS Code ne trouve pas les réglages `.vscode/`).

En cas de problème :

| Message | Cause |
| --- | --- |
| `make.exe` introuvable | MSYS2 n'est pas installé, ou pas dans `C:\msys64` |
| `SDL.h: No such file or directory` | Le paquet SDL n'est pas installé (étape 3) |
| Aucune tâche de build | Le mauvais dossier est ouvert dans VS Code (étape 5) |
| `SDL.dll` introuvable au lancement | Le jeu est lancé hors de VS Code : copier `C:\msys64\ucrt64\bin\SDL.dll` à côté de `platformer.exe` |

## Compilation

### Linux

```bash
make        # compile le jeu
make run    # compile puis lance le jeu
make clean  # supprime les fichiers générés
```

### Windows (VS Code)

| Action | Raccourci |
| --- | --- |
| Compiler | `Ctrl+Shift+B` |
| Lancer | `Ctrl+F5` |
| Lancer avec le débogueur | `F5` |

Le jeu s'ouvre dans une fenêtre de 800×600. Échap ou la croix le ferment.

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
