#ifndef FIREBALL_H
#define FIREBALL_H

#define PI 3.141592653589793238462643383279502884197
#define E 2.718281828459045235360287471352662497757

#include <cmath>
#include <iostream>

#include "Sprite.h"
#include "ParticleEmitter.h"
#include "Spell.h"
#include "Collidable.h"
#include "Character.h"
#include "Timer.h"

class FireBall : public Spell, public Collidable{
    public:
        FireBall(Character* Actor, int ChargeTime, SDL_Texture* Fireball);
        ~FireBall();
        void Update();

        std::vector<Particle> GetParticles();
        Sprite* GetSprite();
        int GetLife();
        void SpellEffect(Collidable& Obj);
        SDL_Rect* GetCollisionRect();

    protected:
        Sprite FireBallSprite;
        float Damage;
        float Speed;
        float DeltaX, DeltaY;
        int LifeSpan;
        Timer FireBallTimer;
        ParticleEmitter* Emitter;
};

#endif // FIREBALL_H
