#include <SDL.h>
#include <windows.h>
#include <iostream>

#include "GameEngine.h"

GameEngine::GameEngine():Render("Un-Named Game", 30, 30 , 1280, 720), _Interface(&Render){
    Running = true;
}
GameEngine::~GameEngine(){
    Render.~Renderer();
}
void GameEngine::Update(){
    int Size = _Interface.GetAllFireBalls().size();
    for (int i = 0; i < Size; i++){
        if (_Interface.GetAllFireBalls()[i].GetLife() <= 0){
            _Interface.GetAllFireBalls().erase(_Interface.GetAllFireBalls().begin() + i);
        }else
            _Interface.GetAllFireBalls()[i].Update();
    }
    Size = _Interface.GetPCs().size();
    for (int i = 0; i < Size; i++){
        _Interface.GetPCs()[i].Update();
    }
    RenderGame();
    HandleEvents();
    HandleMovement(NULL, NULL);
}
void GameEngine::RenderGame(){
    Render.RenderStart();
    Render.RenderParticles(_Interface.GetAllParticles());
    Render.RenderSprites(_Interface.GetAllSprites());
    Render.RenderAnims(_Interface.GetAllAnims());
    Render.RenderFinish();
}
void GameEngine::HandleEvents(){
    bool PC = true;
    if (_Interface.GetPCs().size() == 0)
        PC = false;

    static int CastTime = SDL_GetTicks();
    static bool Casting = false;

    SDL_Event Events;
    while(SDL_PollEvent(&Events)){
        if (Events.type == SDL_QUIT || (Events.type == SDL_KEYDOWN && Events.key.keysym.sym == SDLK_ESCAPE)){   //Handle Escapes
            Running = false;
        }

        if (Events.type == SDL_KEYDOWN){
            if (Events.key.keysym.sym == SDLK_c && PC && !Casting){//Spell Cast
                CastTime = SDL_GetTicks();
                Casting = true;
            }
            if (Events.key.keysym.sym == SDLK_w){
                HandleMovement('w', true);
            }
            if (Events.key.keysym.sym == SDLK_s){
                HandleMovement('s', true);
            }
            if (Events.key.keysym.sym == SDLK_a){
                HandleMovement('a', true);
            }
            if (Events.key.keysym.sym == SDLK_d){
                HandleMovement('d', true);
            }
        }
        if (Events.type == SDL_KEYUP){
            if (Events.key.keysym.sym == SDLK_c && PC){//Spell Cast
                Casting = false;
                _Interface.CreateFireBall(_Interface.GetPCs()[_Interface.ActivePC].GetAnimation().GetX() + _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().GetOrgin()->x,
                                          _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().GetY() + _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().GetOrgin()->y,
                10, 10, _Interface.GetPCs()[_Interface.ActivePC].GetAngle(), SDL_GetTicks() - CastTime);
            }
            if (Events.key.keysym.sym == SDLK_w){
                HandleMovement('w', false);
            }
            if (Events.key.keysym.sym == SDLK_s){
                HandleMovement('s', false);
            }
            if (Events.key.keysym.sym == SDLK_a){
                HandleMovement('a', false);
            }
            if (Events.key.keysym.sym == SDLK_d){
                HandleMovement('d', false);
            }
        }
    }
}
void GameEngine::HandleMovement(char Key, bool Press){
    static bool W, S, A, D;
    static bool V, H;
    bool UpdateAnim;
    switch (Key){
    case 'w':
        if (Press && !W){
            W = true;
            V = true;
            UpdateAnim = true;
            break;
        }
        if (!Press){
            W = false;
            UpdateAnim = true;
            if (V && S)
                V = false;
        }
        break;
    case 's':
        if (Press && !S){
            V = false;
            S = true;
            UpdateAnim = true;
            break;
        }
        if (!Press){
            S = false;
            UpdateAnim = true;
            if (!V && W)
                V = true;
        }
        break;
    case 'd':
        if (Press && !D){
            H = true;
            D = true;
            UpdateAnim = true;
            break;
        }
        if (!Press){
            D = false;
            UpdateAnim = true;
            if (H && A)
                H = false;
        }
        break;
    case 'a':
        if (Press && !A){
            H = false;
            A = true;
            UpdateAnim = true;
            break;
        }
        if (!Press){
            A = false;
            UpdateAnim = true;
            if (!H && D)
                H = true;
        }
        break;
    default:
        if (W && V){
            _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().SetY((float)_Interface.GetPCs()[_Interface.ActivePC].GetAnimation().GetY() - (float).3);//Up
        }
        if (S && !V){
            _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().SetY((float)_Interface.GetPCs()[_Interface.ActivePC].GetAnimation().GetY() + (float).3);//Down
        }
        if (A && !H){
            _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().SetX((float)_Interface.GetPCs()[_Interface.ActivePC].GetAnimation().GetX() - (float).3);//Left
        }
        if (D && H){
            _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().SetX((float)_Interface.GetPCs()[_Interface.ActivePC].GetAnimation().GetX() + (float).3);//Right
        }
        break;
    }

    if (UpdateAnim){
        if (V && W){
            if (H && D){
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Pause();
                _Interface.GetPCs()[_Interface.ActivePC].SetAnimation(4);
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Resume(true);
            }else if (!H && A){
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Pause();
                _Interface.GetPCs()[_Interface.ActivePC].SetAnimation(5);
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Resume(true);
            } else{
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Pause();
                _Interface.GetPCs()[_Interface.ActivePC].SetAnimation(0);
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Resume(true);
            }
        }else if (!V && S){
            if (H && D){
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Pause();
                _Interface.GetPCs()[_Interface.ActivePC].SetAnimation(7);
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Resume(true);
            }else if (!H && A){
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Pause();
                _Interface.GetPCs()[_Interface.ActivePC].SetAnimation(6);
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Resume(true);
            }else{
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Pause();
                _Interface.GetPCs()[_Interface.ActivePC].SetAnimation(1);
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Resume(true);
            }
        }else if (H && D){
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Pause();
            _Interface.GetPCs()[_Interface.ActivePC].SetAnimation(2);
            _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Resume(true);
        }else if (!H && A){
                _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Pause();
            _Interface.GetPCs()[_Interface.ActivePC].SetAnimation(3);
            _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Resume(true);
        }else
            _Interface.GetPCs()[_Interface.ActivePC].GetAnimation().Pause();
    }
}


