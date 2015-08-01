#include <SDL.h>
#include <string>

#include "Character.h"
#include "AnimatedSprite.h"

Character::Character(int NewID, SDL_Texture* CharacterTexture, float PosX, float PosY){
    Anims.push_back(AnimatedSprite(CharacterTexture, PosX, PosY, 0 , 48 , 1, 8, 48, 48, 100, 8));
    Anims.push_back(AnimatedSprite(CharacterTexture, PosX, PosY, 0 , 192, 1, 8, 48, 48, 100, 8));
    Anims.push_back(AnimatedSprite(CharacterTexture, PosX, PosY, 0 , 0  , 1, 8, 48, 48, 100, 8));
    Anims.push_back(AnimatedSprite(CharacterTexture, PosX, PosY, 0 , 336, 1, 8, 48, 48, 100, 8));
    Anims.push_back(AnimatedSprite(CharacterTexture, PosX, PosY, 0 , 96 , 1, 8, 48, 48, 100, 8));
    Anims.push_back(AnimatedSprite(CharacterTexture, PosX, PosY, 0 , 144, 1, 8, 48, 48, 100, 8));
    Anims.push_back(AnimatedSprite(CharacterTexture, PosX, PosY, 0 , 288, 1, 8, 48, 48, 100, 8));
    Anims.push_back(AnimatedSprite(CharacterTexture, PosX, PosY, 0 , 240, 1, 8, 48, 48, 100, 8));
    ActiveAnim = 1;
    for (int i = 0; i < Anims.size(); i ++){
        Anims[i].SetOrgin(24, 24);
        Anims[i].Pause();
    }
    ID = NewID;
}
Character::~Character(){
    Anims.clear();
}
double Character::GetAngle(){
    switch (ActiveAnim){
    case 0:
        return 180;
        break;
    case 1:
        return 0;
        break;
    case 2:
        return 270;
        break;
    case 3:
        return 90;
        break;
    case 4:
        return 225;
        break;
    case 5:
        return 135;
        break;
    case 6:
        return 45;
        break;
    case 7:
        return 315;
        break;
    default:
        return 0;
        break;
    }
}
void Character::SetAnimation(int Direction){
    if (Direction == ActiveAnim)
        return;
    Anims[Direction].SetX((int)Anims[ActiveAnim].GetX());
    Anims[Direction].SetY((int)Anims[ActiveAnim].GetY());
    ActiveAnim = Direction;
}
AnimatedSprite& Character::GetAnimation(int AnimIndex){
        return (AnimIndex = -1) ? Anims[ActiveAnim] : Anims[AnimIndex];
}
void Character::Update(){
    Anims[ActiveAnim].Update();
}
