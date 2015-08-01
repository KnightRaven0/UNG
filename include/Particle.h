#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector2.h"

class Particle{
    public:
        Particle(int X, int Y, int SizeX, int SizeY, float SpeedX, float SpeedY, int LifeTime, SDL_Color ParticleColor);

        SDL_Rect* GetDest();
        SDL_Color GetColor();
        void Update();
        int GetLife();

    protected:
        SDL_Color Color;
        Vector2 Pos;
        int Height, Width;
        float DeltaX, DeltaY;
        int StartTime, LogicalDelay, Life;
};

#endif // PARTICLE_H
