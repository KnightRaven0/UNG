#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Renderable.h"

class Item{
    public:
        Item(SDL_Texture* Texture, SDL_Texture* IconTexture);
        ~Item();

        SDL_Texture* GetIconTex();
        SDL_Texture* GetTex();
        std::string GetName();

    protected:
        std::string Name;
        SDL_Texture* IconTexture;
        SDL_Texture* ItemTexture;
};

#endif // ITEM_H
