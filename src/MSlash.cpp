#include "MSlash.h"

MSlash::MSlash(float X, float Y, Item* Weapon, Character* Parent) : MeleeAttack(X, Y, Weapon, Parent){

}

MSlash::~MSlash(){

}
void MSlash::Update(float X, float Y){

}
SDL_Rect* MSlash::GetCollisionRect(){
    SDL_Rect* Rect = GetDestination();
    int MaxX, MinX;
    int MaxY, MinY;
    if ()
}
