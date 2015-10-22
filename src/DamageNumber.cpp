#include "DamageNumber.h"

#include <stdlib.h>
#include <math.h>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

DamageNumber::DamageNumber(float X, float Y, SDL_Texture* DamageTexture) : Renderable(DamageTexture, X, Y), DamageTimer(10){
    DeltaX = (rand() / (RAND_MAX / .6));
    if (rand() % 2 == 1)
        DeltaX = -DeltaX;
    DeltaY = -(rand() / (RAND_MAX / (float)1)) - .3;
}
DamageNumber::~DamageNumber(){
    SDL_DestroyTexture(Texture);
}
bool DamageNumber::IsDead(){
    if (DeltaY > 1.7)
        return true;
    else
        return false;
}
void DamageNumber::Update(){
    if (DamageTimer.IsTime()){
        SetX(GetX() + DeltaX);
        SetY(GetY() + DeltaY);
        DeltaY += .01;
    }
}
