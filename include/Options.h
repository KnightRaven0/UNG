#ifndef OPTIONS_H
#define OPTIONS_H

#include <SDL.h>

#include "Vector2.h"

class Options{
    public:
        Options(){}

        void LoadOptions();

        SDL_Keycode MovementKeyUP = SDLK_w;
        SDL_Keycode MovementKeyDOWN = SDLK_s;
        SDL_Keycode MovementKeyLEFT = SDLK_a;
        SDL_Keycode MovementKeyRIGHT = SDLK_d;
        SDL_Keycode CombatKeyCAST = SDLK_c;
        Vector2 InvenPos{500, 400};
        Vector2 OptionMenuPos{600, 300};
        Vector2 HealthPos{10, 570};
        Vector2 ManaPos{1100, 570};

        void ChangeKey(SDL_Keycode& KeyToChange);
};

#endif // OPTIONS_H
