#include "menu.h"

static const unsigned char LETTRES[14][7] = {
    {14, 17, 17, 31, 17, 17, 17},
    {14, 17, 16, 16, 16, 17, 14},
    {30, 17, 17, 17, 17, 17, 30},
    {31, 16, 16, 30, 16, 16, 31},
    {17, 17, 17, 31, 17, 17, 17},
    {31, 4, 4, 4, 4, 4, 31},
    {17, 27, 21, 21, 17, 17, 17},
    {17, 25, 21, 19, 17, 17, 17},
    {14, 17, 17, 17, 17, 17, 14},
    {14, 17, 17, 17, 21, 18, 13},
    {30, 17, 17, 30, 20, 18, 17},
    {31, 4, 4, 4, 4, 4, 4},
    {17, 17, 17, 17, 17, 17, 14},
    {0, 0, 0, 31, 0, 0, 0}
};

static const char ALPHABET[] = "ACDEHIMNOQRTU-";

static void dessiner_texte(SDL_Surface *ecran, const char *texte,
                           int x, int y, int taille)
{
    int i, lettre, ligne, colonne;
    SDL_Rect pixel;
    Uint32 blanc = SDL_MapRGB(ecran->format, 255, 255, 255);

    pixel.w = taille;
    pixel.h = taille;

    for (i = 0; texte[i] != '\0'; i++) {
        for (lettre = 0; ALPHABET[lettre] != '\0'; lettre++) {
            if (texte[i] == ALPHABET[lettre]) {
                break;
            }
        }

        if (ALPHABET[lettre] == '\0') {
            continue;
        }

        for (ligne = 0; ligne < 7; ligne++) {
            for (colonne = 0; colonne < 5; colonne++) {
                if (LETTRES[lettre][ligne] & (1 << (4 - colonne))) {
                    pixel.x = x + (i * 6 + colonne) * taille;
                    pixel.y = y + ligne * taille;
                    SDL_FillRect(ecran, &pixel, blanc);
                }
            }
        }
    }
}

static void dessiner_bouton(SDL_Surface *ecran, SDL_Rect bouton,
                            const char *texte, Uint32 couleur)
{
    int longueur = 0;
    int taille = 4;
    int largeur_texte;
    int x, y;

    while (texte[longueur] != '\0') {
        longueur++;
    }

    largeur_texte = (longueur * 6 - 1) * taille;
    x = bouton.x + (bouton.w - largeur_texte) / 2;
    y = bouton.y + (bouton.h - 7 * taille) / 2;

    SDL_FillRect(ecran, &bouton, couleur);
    dessiner_texte(ecran, texte, x, y, taille);
}

ChoixMenu menu_executer(SDL_Surface *ecran)
{
    int selection = 0;
    SDL_Event evenement;

    SDL_Rect bouton_jouer = {0, 220, 400, 60};
    SDL_Rect bouton_quitter = {0, 320, 400, 60};
    SDL_Rect contour;

    Uint32 fond = SDL_MapRGB(ecran->format, 20, 26, 46);
    Uint32 blanc = SDL_MapRGB(ecran->format, 255, 255, 255);
    Uint32 vert = SDL_MapRGB(ecran->format, 40, 140, 70);
    Uint32 rouge = SDL_MapRGB(ecran->format, 170, 50, 50);

    bouton_jouer.x = (ecran->w - bouton_jouer.w) / 2;
    bouton_quitter.x = (ecran->w - bouton_quitter.w) / 2;

    SDL_WM_SetCaption(
        "Tranch - o | Fleches : choisir | Entree : valider",
        NULL);

    while (1) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                return MENU_QUITTER;
            }

            if (evenement.type == SDL_KEYDOWN) {
                switch (evenement.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_DOWN:
                        if (selection == 0) {
                            selection = 1;
                        } else {
                            selection = 0;
                        }
                        break;

                    case SDLK_RETURN:
                        if (selection == 0) {
                            return MENU_JOUER;
                        }
                        return MENU_QUITTER;

                    case SDLK_ESCAPE:
                        return MENU_QUITTER;

                    default:
                        break;
                }
            }
        }

        SDL_FillRect(ecran, NULL, fond);

        dessiner_texte(ecran, "TRANCH - O",
                       (ecran->w - 354) / 2, 110, 6);

        if (selection == 0) {
            contour = bouton_jouer;
        } else {
            contour = bouton_quitter;
        }

        contour.x -= 4;
        contour.y -= 4;
        contour.w += 8;
        contour.h += 8;

        SDL_FillRect(ecran, &contour, blanc);

        dessiner_bouton(ecran, bouton_jouer, "DEMARRER", vert);
        dessiner_bouton(ecran, bouton_quitter, "QUITTER", rouge);

        SDL_Flip(ecran);
        SDL_Delay(16);
    }
}