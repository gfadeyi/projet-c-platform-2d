#ifndef MENU_H
#define MENU_H

#include <SDL.h>

typedef enum {
    MENU_JOUER = 0,
    MENU_QUITTER = 1
} ChoixMenu;

ChoixMenu menu_executer(SDL_Surface *ecran);

#endif