#include "Button.h"

Button::Button(int CenterX, int CenterY, SDL_Texture* ButtonTexture, SDL_Texture* ButtonText) : ButtonSprite(ButtonTexture, 0, 0), TextSprite(ButtonText, 0, 0){
    SDL_Rect* ButtonRect = ButtonSprite.GetDestination();
    SDL_Rect* TextRect = TextSprite.GetDestination();
    ButtonSprite.SetDestinationSize(ButtonRect->w / 2, ButtonRect->h);
    ButtonSprite.SetCliping(0, 0, ButtonRect->w / 2, ButtonRect->h);
    ButtonSprite.SetX(CenterX - ButtonRect->w / 4);
    ButtonSprite.SetY(CenterY + ButtonRect->h / 2);
    TextSprite.SetX(CenterX - TextRect->w / 2);
    TextSprite.SetY(CenterY + TextRect->h);
    delete[] ButtonRect;
    delete[] TextRect;
}

Button::~Button(){

}
bool Button::CheckWithin(float X, float Y){
    SDL_Rect* Dest = ButtonSprite.GetDestination();
    bool Within = true;
    if (Dest->x + Dest->w < X)
        Within = false;
    else if (X < Dest->x)
        Within = false;
    else if (Dest->y + Dest->h < Y)
        Within= false;
    else if (Y < Dest->y)
        Within = false;
    delete[] Dest;
    if (Within && !Hovered){
        SDL_Rect* Clip = ButtonSprite.GetCliping();
        ButtonSprite.SetCliping(Clip->w, 0, Clip->w, Clip->h);
        delete[] Clip;
        Hovered = true;
    }else if (!Within && Hovered){
        SDL_Rect* Clip = ButtonSprite.GetCliping();
        ButtonSprite.SetCliping(0, 0, Clip->w, Clip->h);
        delete[] Clip;
        Hovered = false;
    }
    return Within;
}
std::vector<Sprite*> Button::GetSprites(){
    std::vector<Sprite*> Temp;
    Temp.push_back(&ButtonSprite);
    Temp.push_back(&TextSprite);
    return Temp;
}
