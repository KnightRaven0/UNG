#ifndef FIREBALL_H
#define FIREBALL_H

#define PI 3.141592653589793238462643383279502884197
#define E 2.718281828459045235360287471352662497757

#include <cmath>

#include "Sprite.h"
#include "ParticleEmitter.h"

class FireBall{
    public:
        FireBall(int ID, float X, float Y, int Intel, int Wit, double Angle, int ChargeTime, SDL_Texture* Fireball):FireBallSprite(Fireball, X, Y),
        Emitter(40, 6, 3, 6, 3, 200, 50, 500, 750, 20){
            if (ChargeTime > 10000)
                ChargeTime = 10000;
            Damage = (ChargeTime / 1000 + 1) * (rand() % (Wit * 2)) + Intel;
            Speed = 65 * Wit; //FIXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            Size = .2 + ((float)ChargeTime / 500);        //FIXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            Accuracy = 1 / (pow(E, (-ChargeTime / 4000)));
            DeltaX = cos((Angle + 90) * (PI / 180)) * Speed / 100;
            DeltaY = sin((Angle + 90) * (PI / 180)) * Speed / 100;
            LifeSpan = 1.5 * ChargeTime + 400;
            Emitter.AddColor(255, 0, 0);
            Emitter.AddColor(200, 90, 0);
            Emitter.AddColor(160, 160, 0);
            Emitter.AddColor(100, 0, 0);
            Emitter.AddColor(179,30, 0);
            Emitter.AddColor(255, 255, 0);
            FireBallSprite.SetScale(Size);
            FireBallSprite.SetX(FireBallSprite.GetX() - FireBallSprite.GetOrgin()->x);
            FireBallSprite.SetY(FireBallSprite.GetY() - FireBallSprite.GetOrgin()->y);
            StartTime = SDL_GetTicks();
            Delay = 10;
            LogicalDelay = 10;
        }
        ~FireBall();
        void Update();

        std::vector<Particle> GetParticles();
        Sprite GetSprite();
        int GetLife();

    protected:
        Sprite FireBallSprite;
        float Damage;
        float Speed;
        float Accuracy; //1 max, 0 min
        float Size;
        float DeltaX, DeltaY;
        int LifeSpan;
        int StartTime, Delay, LogicalDelay;
        ParticleEmitter Emitter;
};

#endif // FIREBALL_H
