#ifndef BUTTON_H
#define BUTTON_H

#include <vector>

#include "Sprite.h"

class Button{
    public:
        Button(int X, int Y, SDL_Texture* ButtonTexture, SDL_Texture* ButtonText);
        ~Button();

        bool CheckWithin(float X, float Y);
        std::vector<Sprite*> GetSprites();

    protected:
        Sprite ButtonSprite;
        Sprite TextSprite;
        bool Hovered;
};

#endif // BUTTON_H
