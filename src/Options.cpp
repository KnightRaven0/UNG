#include "Options.h"

void Options::ChangeKey(SDL_Keycode& KeyToChange){
    SDL_Event Events;
    while(SDL_PollEvent(&Events)){
        if (Events.type == SDL_KEYDOWN){
            KeyToChange = Events.key.keysym.sym;
        }
    }
}
