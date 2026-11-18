#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "config.h"
#include "joueur.h"
#include "hud.h"

#define DELAI_IMAGE_MS 16

#define DT_MAX 0.05f

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    SDL_Event evenement;
    int continuer = 1;
    Joueur joueur;
    SDL_Rect sol;
    Uint32 temps_precedent;
    Uint32 temps_actuel;
    float dt;

    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32,
                             SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) {
        fprintf(stderr, "Erreur SDL_SetVideoMode : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("Platform 2D", NULL);

    joueur_initialiser(&joueur, 100.0f, 100.0f);
    sol.x = 0;
    sol.y = SOL_Y;
    sol.w = LARGEUR_FENETRE;
    sol.h = HAUTEUR_FENETRE - SOL_Y;

    temps_precedent = SDL_GetTicks();

    while (continuer) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                continuer = 0;
            } else if (evenement.type == SDL_KEYDOWN
                       && evenement.key.keysym.sym == SDLK_ESCAPE) {
                continuer = 0;
            } else if (evenement.type == SDL_KEYDOWN
                       && evenement.key.keysym.sym == SDLK_k) {
                joueur_changer_pv(&joueur, -1);
            } else if (evenement.type == SDL_KEYDOWN
                       && evenement.key.keysym.sym == SDLK_h) {
                joueur_changer_pv(&joueur, 1);
            }
        }

        temps_actuel = SDL_GetTicks();
        dt = (float)(temps_actuel - temps_precedent) / 1000.0f;
        temps_precedent = temps_actuel;
        if (dt > DT_MAX) {
            dt = DT_MAX;
        }

        joueur_lire_clavier(&joueur, SDL_GetKeyState(NULL));
        joueur_mettre_a_jour(&joueur, dt);

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0x00, 0x4C, 0xFF));
        SDL_FillRect(ecran, &sol, SDL_MapRGB(ecran->format, 60, 160, 60));
        joueur_dessiner(&joueur, ecran);
        hud_dessiner_barre_vie(ecran, joueur.pv, joueur.pv_max);

        SDL_Flip(ecran);

        SDL_Delay(DELAI_IMAGE_MS);
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
