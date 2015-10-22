#include "UserInterface.h"
#include "Options.h"

#include <iostream>

UserInterface::UserInterface(Interface* Inter){
    HealthSprite = new Sprite(Inter->Render->GetTexture("Resources//Textures//HPUnderlay.png"), Option.HealthPos.GetX(), Option.HealthPos.GetY());
    ManaSprite = new Sprite(Inter->Render->GetTexture("Resources//Textures//MPUnderlay.png"), Option.ManaPos.GetX(), Option.ManaPos.GetY());
    HealthBar = new Sprite(Inter->Render->GetTexture("Resources//Textures//Overlay.png"), Option.HealthPos.GetX(), Option.HealthPos.GetY());
    ManaBar = new Sprite(Inter->Render->GetTexture("Resources//Textures//Overlay.png"), Option.ManaPos.GetX(), Option.ManaPos.GetY());
    SDL_Rect* TempRect = HealthSprite->GetDestination();
    HealthSize.SetX(TempRect->w);
    HealthSize.SetY(TempRect->h);
    delete[] TempRect;
    TempRect = ManaSprite->GetDestination();
    ManaSize.SetX(TempRect->w);
    ManaSize.SetY(TempRect->h);
    delete[] TempRect;
}

UserInterface::~UserInterface(){
    delete HealthSprite;
    delete ManaSprite;
    delete HealthBar;
    delete ManaBar;
}
void UserInterface::Update(Character Actor){
    HealthSprite->SetCliping(0, HealthSize.GetY() - HealthSize.GetY() * Actor.GetHealth() / Actor.GetMaxHealth(), HealthSize.GetX(), HealthSize.GetY() * Actor.GetHealth() / Actor.GetMaxHealth());
    HealthSprite->SetY(Option.HealthPos.GetY() + HealthSize.GetY() - HealthSize.GetY() * Actor.GetHealth() / Actor.GetMaxHealth());
    HealthSprite->SetDestinationSize(HealthSize.GetX(), HealthSize.GetY() * Actor.GetHealth() / Actor.GetMaxHealth());
    ManaSprite->SetCliping(0, ManaSize.GetY() - ManaSize.GetY() * Actor.GetMana() / Actor.GetMaxMana(), ManaSize.GetX(), ManaSize.GetY() * Actor.GetMana() / Actor.GetMaxMana());
    ManaSprite->SetY(Option.ManaPos.GetY() + ManaSize.GetY() - ManaSize.GetY() * Actor.GetMana() / Actor.GetMaxMana());
    ManaSprite->SetDestinationSize(ManaSize.GetX(), ManaSize.GetY() * Actor.GetMana() / Actor.GetMaxMana());
}
std::vector<Sprite*> UserInterface::GetUISprites(){
    std::vector<Sprite*> Temp;
    Temp.push_back(HealthSprite);
    Temp.push_back(ManaSprite);
    Temp.push_back(HealthBar);
    Temp.push_back(ManaBar);
    return Temp;
}
