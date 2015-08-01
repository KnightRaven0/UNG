#include <windows.h>

#include <SDL.h>

#include "FireBall.h"

void FireBall::Update(){
    if (SDL_GetTicks() - StartTime >= LogicalDelay){
        LogicalDelay += Delay;
        FireBallSprite.SetX(FireBallSprite.GetX() + DeltaX);
        FireBallSprite.SetY(FireBallSprite.GetY() + DeltaY);
        LifeSpan -= Delay;
    }
    Emitter.Update(FireBallSprite.GetX() + FireBallSprite.GetOrgin()->x, FireBallSprite.GetY()+ FireBallSprite.GetOrgin()->y);
}

std::vector<Particle> FireBall::GetParticles(){return Emitter.GetParticles();}
Sprite FireBall::GetSprite(){return FireBallSprite;}
int FireBall::GetLife(){
    return LifeSpan;
}
FireBall::~FireBall(){
    Emitter.~ParticleEmitter();
    FireBallSprite.~Sprite();
}
