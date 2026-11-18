#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

#define DELAI_IMAGE_MS 16

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    SDL_Event evenement;
    int continuer = 1;

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

    while (continuer) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                continuer = 0;
            } else if (evenement.type == SDL_KEYDOWN
                       && evenement.key.keysym.sym == SDLK_ESCAPE) {
                continuer = 0;
            }
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0x00, 0x4C, 0xFF));

        SDL_Flip(ecran);

        SDL_Delay(DELAI_IMAGE_MS);
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
