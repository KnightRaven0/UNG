#ifndef MELEEATTACK_H
#define MELEEATTACK_H

#include "SDL.h"

#include "Collidable.h"
#include "Item.h"
#include "AnimatedSprite.h"

class Character;

class MeleeAttack : public Collidable{
    public:
        MeleeAttack(float X, float Y, Item* Weapon, Character* Parent);
        virtual ~MeleeAttack();
        virtual void Update(float X, float Y) = 0;
        virtual SDL_Rect* GetCollisionRect() = 0;

    protected:
        float Damage;
        float Speed;
        float AOEEffect;
        float Delay;

        //float SpeedIncrease;
        //bool Backswing;
};

#endif // MELEEATTACK_H
