#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H
#define PI 3.141592653589793238462643383279502884197

#include <vector>
#include <SDL.h>

#include "Particle.h"
#include "Timer.h"

class ParticleEmitter{
    public:
        ParticleEmitter(int MaxParticles, int MaxSizeX, int MinSizeX, int MaxSizeY, int MinSizeY, float MaxSpeed, int MinSpeed, int LifeMin, int LifeMax);
        ~ParticleEmitter();

        void Update(float X, float Y);
        void AddColor(Uint8 Red, Uint8 Green, Uint8 Blue);
        std::vector<Particle> GetParticles();

    protected:
        std::vector<Particle> Particles;
        std::vector<SDL_Color> Colors;
        int Max;
        int XMax, XMin, YMax, YMin;
        int LMax, LMin;
        float SMin, SMax;
        Timer ParticleEmitterTimer;
};

#endif // PARTICLEEMITTER_H
