#ifndef SPELL_H
#define SPELL_H

#include <SDL.h>
#include <iostream>

#include "Character.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "Particle.h"

class Spell{
    public:
        virtual ~Spell(){}
        virtual void Update() = 0;
        virtual void SpellEffect(Collidable& Obj) = 0;
        virtual Sprite* GetSprite() = 0;
        virtual std::vector<Particle> GetParticles() = 0;
        virtual int GetLife() = 0;
};
#endif // SPELL_H
