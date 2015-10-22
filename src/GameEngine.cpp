#include <SDL.h>
#include <windows.h>
#include <iostream>
#include <typeinfo>

#include "GameEngine.h"
#include "MasterControl.h"

GameEngine::GameEngine(Renderer* RenderEngine): Inter(RenderEngine), UI(&Inter), CollisionTimer(16), RenderTimer(10), MovementTimer(1){
    Render = RenderEngine;
    W = false;
    S = false;
    A = false;
    D = false;
    Timer::InitializeTime();
    Timer::SetGameSpeed(1);
    Timer::UnpauseGame();
    Inter.CreatePlayableCharacter(100, 100);
    Inter.CreateCharacter(400, 100);
}
void GameEngine::Pause(){
    Timer::PauseGame();
}
void GameEngine::Resume(){
    Timer::UnpauseGame();
}
void GameEngine::Update(MasterControl* Control){
    Timer::Update();
    HandleEvents(Control);
    UpdateObjects();
    if (CollisionTimer.IsTime()){
        CollisionDetection();
    }
    if (RenderTimer.IsTime()){
        Draw();
    }
}
void GameEngine::CollisionDetection(){
    std::vector<Collidable*> Collides = Inter.GetCollidables();
    for (int c = 0; c < Collides.size(); c++){
        for (int cc = c + 1; cc < Collides.size(); cc++){
            SDL_Rect* FirstDest = Collides[c]->GetCollisionRect();
            SDL_Rect* SecondDest = Collides[cc]->GetCollisionRect();
            bool Collision = true;
            if (FirstDest->x + FirstDest->w < SecondDest->x)
                Collision = false;
            else if (SecondDest->x + SecondDest->w < FirstDest->x)
                Collision = false;
            else if (FirstDest->y + FirstDest->h < SecondDest->y)
                Collision = false;
            else if (SecondDest->y + SecondDest->h < FirstDest->y)
                Collision = false;
            if (Collision){
                Collidable& Ref1 = *Collides[c];
                Collidable& Ref2 = *Collides[cc];
                if (dynamic_cast<Identification*>(&Ref1)){
                    Collision = !Ref1.ShouldIgnore(Ref2);
                }
                if (dynamic_cast<Identification*>(&Ref1) && Collision){
                    Collision = !Ref2.ShouldIgnore(Ref1);
                }
                if (Collision){
                    if (dynamic_cast<Spell*>(&Ref1) != NULL){
                        dynamic_cast<Spell*>(&Ref1)->SpellEffect(Ref2);
                    }
                    if (dynamic_cast<Spell*>(&Ref2) != NULL){
                        dynamic_cast<Spell*>(&Ref2)->SpellEffect(Ref1);
                    }
                    Collides[c]->Collided();
                    Collides[cc]->Collided();
                }
            }
            delete[] FirstDest;
            delete[] SecondDest;
        }
    }
}
void GameEngine::ForceCollisionCheck(Collidable* Collide){
    std::vector<Collidable*> Collides = Inter.GetCollidables();
    for (int c = 0; c < Collides.size(); c++){
        SDL_Rect* FirstDest = Collide->GetCollisionRect();
        SDL_Rect* SecondDest = Collides[c]->GetCollisionRect();
        bool Collision = true;
        if (FirstDest->x + FirstDest->w < SecondDest->x)
            Collision = false;
        else if (SecondDest->x + SecondDest->w < FirstDest->x)
            Collision = false;
        else if (FirstDest->y + FirstDest->h < SecondDest->y)
            Collision = false;
        else if (SecondDest->y + SecondDest->h < FirstDest->y)
            Collision = false;
        if (Collision){
            Collidable& Ref1 = *Collide;
            Collidable& Ref2 = *Collides[c];
            if (dynamic_cast<Identification*>(&Ref1)){
                Collision = !Ref1.ShouldIgnore(Ref2);
            }
            if (dynamic_cast<Identification*>(&Ref1) && Collision){
                Collision = !Ref2.ShouldIgnore(Ref1);
            }
            if (Collision){
                if (dynamic_cast<Spell*>(&Ref1) != NULL){
                    dynamic_cast<Spell*>(&Ref1)->SpellEffect(Ref2);
                }
                if (dynamic_cast<Spell*>(&Ref2) != NULL){
                    dynamic_cast<Spell*>(&Ref2)->SpellEffect(Ref1);
                }
                Collide->Collided();
                Collides[c]->Collided();
            }
        }
        delete[] FirstDest;
        delete[] SecondDest;
    }
}
void GameEngine::UpdateObjects(){
    int Size = Inter.GetSpells().size();
    for (int i = Size - 1; i >= 0; i--){
        if (Inter.GetSpells()[i]->GetLife() <= 0){
            Inter.PreserveParticles(Inter.GetSpells()[i]->GetParticles());
            delete Inter.GetSpells()[i];
            Inter.GetSpells().erase(Inter.GetSpells().begin() + i);
        }else{
            Inter.GetSpells()[i]->Update();
        }
    }
    Size = Inter.GetPCs().size();
    for (int i = 0; i < Size; i++){
        Inter.GetPCs()[i].Update();
    }
    Size = Inter.GetNPCs().size();
    for (int i = 0; i < Size; i++){
        Inter.GetNPCs()[i].Update();
    }
    Size = Inter.GetStrayParticles().size();
    for (int i = Size - 1; i >= 0; i--){
        Inter.GetStrayParticles()[i].Update();
        if (Inter.GetStrayParticles()[i].GetLife() <= 0)
            Inter.GetStrayParticles().erase(Inter.GetStrayParticles().begin() + i);
    }
    Size = Inter.GetDamageNumbers().size();
    for (int i = Size - 1; i >= 0; i--){
        if (Inter.GetDamageNumbers()[i]->IsDead()){
            delete Inter.GetDamageNumbers()[i];
            Inter.GetDamageNumbers().erase(Inter.GetDamageNumbers().begin() + i);
        }else
            Inter.GetDamageNumbers()[i]->Update();
    }
    while (MovementTimer.IsTime()){
        if (W)
            Inter.GetPCs()[ActivePC].MoveForward(100);
        if (S)
            Inter.GetPCs()[ActivePC].MoveForward(-75);
        if (D)
            Inter.GetPCs()[ActivePC].Rotate(.2);
        if (A)
            Inter.GetPCs()[ActivePC].Rotate(-.2);
    }
    UI.Update(Inter.GetPCs()[ActivePC]);
}
void GameEngine::Draw(){
    Render->RenderStart();
    Render->RenderSprites(Inter.GetMapSprites());
    Render->RenderParticles(Inter.GetStrayParticles());
    Render->RenderParticles(Inter.GetAllParticles());
    Render->RenderSprites(Inter.GetAllSprites());
    Render->RenderAbles(Inter.GetRenderables());
    Render->RenderSprites(UI.GetUISprites());
    Render->RenderFinish();
}
void GameEngine::HandleEvents(MasterControl* Control){
    UpdateAnim = false;
    bool PC = true;
    if (Inter.GetPCs().size() == 0){
        PC = false;
    }
    static int CastTime;
    static bool Casting = false;

    SDL_Event Events;
    while(SDL_PollEvent(&Events)){
        if (Events.type == SDL_QUIT || (Events.type == SDL_KEYDOWN && Events.key.keysym.sym == SDLK_ESCAPE)){
            Control->PopState();
        }
        if (Events.type == SDL_KEYDOWN){
            if (Events.key.keysym.sym == Option.CombatKeyCAST && PC && !Casting){
                CastTime = Timer::GetTicks();
                Casting = true;
            }
            if (Events.key.keysym.sym == Option.MovementKeyUP){
                if (!W){
                    W = true;
                    V = true;
                }
            }
            if (Events.key.keysym.sym == Option.MovementKeyDOWN){
                if (!S){
                    V = false;
                    S = true;
                }
            }
            if (Events.key.keysym.sym == Option.MovementKeyLEFT){
                if (!A){
                    H = false;
                    A = true;
                }
            }
            if (Events.key.keysym.sym == Option.MovementKeyRIGHT){
                if (!D){
                    H = true;
                    D = true;
                }
            }
        }
        if (Events.type == SDL_KEYUP){
            if (Events.key.keysym.sym == Option.CombatKeyCAST && PC){
                Casting = false;
                Inter.CastSpell(&Inter.GetPCs()[ActivePC], Timer::GetTicks() - CastTime);
            }
            if (Events.key.keysym.sym == Option.MovementKeyUP){
                W = false;
                if (V && S)
                    V = false;
            }
            if (Events.key.keysym.sym == Option.MovementKeyDOWN){
                S = false;
                if (!V && W)
                    V = true;
            }
            if (Events.key.keysym.sym == Option.MovementKeyLEFT){
                A = false;
                if (!H && D)
                    H = true;
            }
            if (Events.key.keysym.sym == Option.MovementKeyRIGHT){
                D = false;
                if (H && A)
                    H = false;
            }
        }
    }
}
