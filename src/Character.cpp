#include <SDL.h>
#include <string>
#include <math.h>

#include "Character.h"
#include "AnimatedSprite.h"
#include "Interface.h"

Character::Character(SDL_Texture* CharacterTexture, float PosX, float PosY, Interface* CreationInterface) : RegenTimer(10), RegenNumberTimer(1000), MovementTimer(10){
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
        Anims[i].Pause();
    }
    Inter = CreationInterface;
    DeltaX = 0;
    DeltaY = 0;
    CharacterAngle = 0;
    Health = 100;
    MaxHealth = 100;
    Mana = 100;
    MaxMana = 100;
    CurrentSpellID = 1;
    Str = 10;
    Con = 10;
    End = 10;
    Int = 10;
    Wit = 10;
    Wil = 10;
    Dex = 10;
    Agi = 10;
    Chr = 10;
}
Character::~Character(){
    Anims.clear();
}

double Character::GetAngle(){
    return CharacterAngle;
}
void Character::SetAnimation(int Direction){
    Anims[ActiveAnim].Pause();
    if (Direction == ActiveAnim)
        return;
    Anims[Direction].SetX((int)Anims[ActiveAnim].GetX());
    Anims[Direction].SetY((int)Anims[ActiveAnim].GetY());
    ActiveAnim = Direction;
    Anims[ActiveAnim].Resume(true);
}
AnimatedSprite* Character::GetAnimation(int AnimIndex){
    return (AnimIndex = -1) ? &Anims[ActiveAnim] : &Anims[AnimIndex];
}
SDL_Rect* Character::GetCollisionRect(){
    return Anims[ActiveAnim].GetDestination();
}
void Character::Update(){
    if (RegenTimer.IsTime()){
        if (Health < MaxHealth){
            Health += HealthRegen;
            HealthPastSec += HealthRegen;
            if (Health > MaxHealth){
                HealthPastSec -= Health - MaxHealth;
                Health = MaxHealth;
            }
        }
        if (Mana < MaxMana){
            Mana += ManaRegen;
            ManaPastSec += ManaRegen;
            if (Mana > MaxMana){
                ManaPastSec -= Mana - MaxMana;
                Mana = MaxMana;
            }
        }
    }
    if (RegenNumberTimer.IsTime()){
        if (HealthPastSec > 0){
            Inter->CreateDamageNumber(Anims[ActiveAnim].GetX(), Anims[ActiveAnim].GetY(), HealthPastSec, 1);
            HealthPastSec = 0;
        }
        if (ManaPastSec > 0){
            Inter->CreateDamageNumber(Anims[ActiveAnim].GetX(), Anims[ActiveAnim].GetY(), ManaPastSec, 4);
            ManaPastSec = 0;
        }
    }
    if (MovementTimer.IsTime()){
        if (DeltaX != 0 || DeltaY != 0){
            Anims[ActiveAnim].Resume();
            Anims[ActiveAnim].ModX(DeltaX / 100);
            Anims[ActiveAnim].ModY(DeltaY / 100);
            DeltaX = DeltaX * .95;
            DeltaY = DeltaY * .95;
            Anims[ActiveAnim].Update();
            if (abs(DeltaX) < .001)
                DeltaX = 0;
            if (abs(DeltaY) < .001)
                DeltaY = 0;
        }else{
            Anims[ActiveAnim].Pause();
        }
    }
    static float OldCharacterAngle;
    if (CharacterAngle != OldCharacterAngle){
        OldCharacterAngle = CharacterAngle;
        while (CharacterAngle < 0)
            CharacterAngle += 360;
        CharacterAngle = fmod(CharacterAngle, 360);
        if ((22.5  > CharacterAngle || CharacterAngle > 337.5) && ActiveAnim != 1)
            SetAnimation(1);
        if ((22.5  < CharacterAngle && CharacterAngle < 67.5 ) && ActiveAnim != 6)
            SetAnimation(6);
        if ((67.5  < CharacterAngle && CharacterAngle < 112.5) && ActiveAnim != 3)
            SetAnimation(3);
        if ((112.5 < CharacterAngle && CharacterAngle < 157.5) && ActiveAnim != 5)
            SetAnimation(5);
        if ((157.5 < CharacterAngle && CharacterAngle < 202.5) && ActiveAnim != 0)
            SetAnimation(0);
        if ((202.5 < CharacterAngle && CharacterAngle < 247.5) && ActiveAnim != 4)
            SetAnimation(4);
        if ((247.5 < CharacterAngle && CharacterAngle < 292.5) && ActiveAnim != 2)
            SetAnimation(2);
        if ((292.5 < CharacterAngle && CharacterAngle < 337.5) && ActiveAnim != 7)
            SetAnimation(7);
    }
}
void Character::Rotate(double RotateAmount){
    CharacterAngle += RotateAmount;
}
void Character::MoveForward(float PercentSpeed){
    DeltaX += PercentSpeed / 100 * MaxSpeed / 1000 * cos((CharacterAngle + 90) / 180 * M_PI);
    DeltaY += PercentSpeed / 100 * MaxSpeed / 1000 * sin((CharacterAngle + 90) / 180 * M_PI);
}
void Character::DoDamage(float DamageDone){
    if (DamageDone > 0){
        //DamageDone = DamageDone * Armor or whatever
        Health -= DamageDone;
        Inter->CreateDamageNumber(Anims[ActiveAnim].GetX(), Anims[ActiveAnim].GetY(), DamageDone, 0);
    }
}
float Character::GetHealth(){
    return Health;
}
float Character::GetMaxHealth(){
    return MaxHealth;
}
float Character::GetMana(){
    return Mana;
}
float Character::GetMaxMana(){
    return MaxMana;
}
void Character::Heal(float HealthRestored){
    Health += HealthRestored;
    Inter->CreateDamageNumber(Anims[ActiveAnim].GetX(), Anims[ActiveAnim].GetY(), HealthRestored, 1);
}
void Character::SetHealth(float NewHealth){

}
void Character::SpendMana(float SpentMana){
    Mana -= SpentMana;
    Inter->CreateDamageNumber(Anims[ActiveAnim].GetX(), Anims[ActiveAnim].GetY(), SpentMana, 3);
}
void Character::RestoreMana(float AmountRestored){

}
void Character::SetMana(float NewMana){

}
bool Character::IsAlive(){return (Health > 0) ? true : false;}


int Character::GetStr(){
    return Str;
}
int Character::GetCon(){
    return Con;
}
int Character::GetEnd(){
    return End;
}
int Character::GetInt(){
    return Int;
}
int Character::GetWit(){
    return Wit;
}
int Character::GetWil(){
    return Wil;
}
int Character::GetDex(){
    return Dex;
}
int Character::GetAgi(){
    return Agi;
}
int Character::GetChr(){
    return Chr;
}
int Character::GetCurrentSpellID(){
    return CurrentSpellID;
}
