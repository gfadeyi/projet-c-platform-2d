/*
 * main.c - Point d'entrée du jeu de plateforme 2D.
 *
 * Ouvre une fenêtre SDL 1.2 et fait tourner la boucle de jeu :
 * lire les événements, mettre à jour, dessiner, attendre.
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

/* Taille de la fenêtre en pixels */
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

/* Pause entre deux images : 16 ms donne environ 60 images par seconde */
#define DELAI_IMAGE_MS 16

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL; /* la zone de dessin de la fenêtre */
    SDL_Event evenement;       /* un événement lu dans la file de SDL */
    int continuer = 1;         /* 1 tant que le jeu tourne, 0 pour quitter */

    /* On n'utilise pas les arguments de la ligne de commande :
       le (void) évite un avertissement "paramètre non utilisé" */
    (void)argc;
    (void)argv;

    /* 1. Démarrer la partie vidéo de SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* 2. Ouvrir la fenêtre : 32 bits par pixel, double tampon */
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32,
                             SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) {
        fprintf(stderr, "Erreur SDL_SetVideoMode : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("Platform 2D", NULL);

    /* 3. Boucle de jeu */
    while (continuer) {
        /* a) Lire tous les événements en attente */
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                continuer = 0; /* clic sur la croix */
            } else if (evenement.type == SDL_KEYDOWN
                       && evenement.key.keysym.sym == SDLK_ESCAPE) {
                continuer = 0; /* touche Échap */
            }
        }

        /* b) Dessiner : remplir tout l'écran en bleu #004CFF
              (rouge 0x00, vert 0x4C, bleu 0xFF, en hexadécimal) */
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0x00, 0x4C, 0xFF));

        /* c) Afficher l'image qu'on vient de dessiner */
        SDL_Flip(ecran);

        /* d) Laisser respirer le processeur */
        SDL_Delay(DELAI_IMAGE_MS);
    }

    /* 4. Libérer SDL avant de quitter */
    SDL_Quit();
    return EXIT_SUCCESS;
}
