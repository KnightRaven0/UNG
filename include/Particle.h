#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector2.h"
#include "Timer.h"

class Particle : public Vector2{
    public:
        Particle(int X, int Y, int SizeX, int SizeY, float SpeedX, float SpeedY, int LifeTime, SDL_Color ParticleColor);
        ~Particle();

        SDL_Rect* GetDest();
        SDL_Color GetColor();
        void Update();
        int GetLife();

    protected:
        SDL_Color Color;
        int Height, Width;
        float DeltaX, DeltaY;
        int Life;
        Timer ParticleTimer;
};

#endif // PARTICLE_H
