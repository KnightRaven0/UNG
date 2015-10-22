#ifndef DAMAGENUMBER_H
#define DAMAGENUMBER_H

#include "Renderable.h"
#include "Timer.h"

class DamageNumber : public Renderable{
    public:
        DamageNumber(float X, float Y, SDL_Texture* DamageTexture);
        ~DamageNumber();
        void Update();

        bool IsDead();

    protected:
        float DeltaX, DeltaY;
        Timer DamageTimer;
};

#endif // DAMAGENUMBER_H
