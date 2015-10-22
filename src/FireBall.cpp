#include <windows.h>
#include <SDL.h>
#include <iostream>

#include "FireBall.h"

FireBall::FireBall(Character* Actor, int ChargeTime, SDL_Texture* Fireball) : FireBallSprite(Fireball, Actor->GetAnimation()->GetX(), Actor->GetAnimation()->GetY()), FireBallTimer(10), Collidable(Actor->GetID()){
    if (ChargeTime > 10000)
        ChargeTime = 10000;
    if (ChargeTime == 0){
        ChargeTime = 1;
    }
    if (Actor->GetMana() < (5 + sqrt(ChargeTime / 100))){
        LifeSpan = -1;
    }else{
        Actor->SpendMana(5 + sqrt(ChargeTime / 100));
        LifeSpan = .7 * ChargeTime + 300;
    }
    FireBallSprite.SetScale(.2 + ((float)ChargeTime / 3000));
    SDL_Point* FireBallOrigin = FireBallSprite.GetOrigin();
    SDL_Point* ActorOrigin = Actor->GetAnimation()->GetOrigin();
    FireBallSprite.ModX(ActorOrigin->x - FireBallOrigin->x);
    FireBallSprite.ModY(ActorOrigin->y - FireBallOrigin->y);
    delete[] FireBallOrigin;
    delete[] ActorOrigin;
    Speed = (float)60 * (float)Actor->GetWit() / sqrt((ChargeTime / 1000) + .6);
    DeltaX = cos((Actor->GetAngle() + 90) * (PI / 180)) * Speed / 100;
    DeltaY = sin((Actor->GetAngle() + 90) * (PI / 180)) * Speed / 100;
    Damage = sqrt((ChargeTime / 1000) + .15) * ((float)(rand() % (Actor->GetWit() * 2)) + (float)Actor->GetInt());
    Emitter = new ParticleEmitter(10 + ChargeTime / 150, 3 + ChargeTime / 500, 1 + ChargeTime / 1000, 3 + ChargeTime / 500, 1 + ChargeTime / 1000, 200, 50, 500, 750);
    Emitter->AddColor(255, 0  , 0);
    Emitter->AddColor(200, 90 , 0);
    Emitter->AddColor(160, 160, 0);
    Emitter->AddColor(100, 0  , 0);
    Emitter->AddColor(179, 30 , 0);
    Emitter->AddColor(255, 255, 0);
}
FireBall::~FireBall(){
    delete Emitter;
}

void FireBall::Update(){
    while (FireBallTimer.IsTime()){
        FireBallSprite.ModX(DeltaX);
        FireBallSprite.ModY(DeltaY);
        FireBallSprite.SetAngle(FireBallSprite.GetAngle() + 10);
        LifeSpan -= 10;
    }
    SDL_Point* Origin = FireBallSprite.GetOrigin();
    Emitter->Update(FireBallSprite.GetX() + Origin->x, FireBallSprite.GetY()+ Origin->y);
    delete Origin;
}
void FireBall::SpellEffect(Collidable& Obj){
    if (dynamic_cast<Character*>(&Obj) != NULL && (LifeSpan > 0)){
        dynamic_cast<Character*>(&Obj)->DoDamage(Damage);
        LifeSpan = -1;
    }
}
std::vector<Particle> FireBall::GetParticles(){return Emitter->GetParticles();}
Sprite* FireBall::GetSprite(){return &FireBallSprite;}
int FireBall::GetLife(){return LifeSpan;}

SDL_Rect* FireBall::GetCollisionRect(){
    return FireBallSprite.GetDestination();
}
