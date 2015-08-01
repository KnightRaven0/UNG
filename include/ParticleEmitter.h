#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#define PI 3.141592653589793238462643383279502884197

#include "Particle.h"
#include <vector>

class ParticleEmitter
{
    public:
        ParticleEmitter(int MaxParticles, int MaxSizeX, int MinSizeX, int MaxSizeY, int MinSizeY,
                        float MaxSpeed, int MinSpeed, int LifeMin, int LifeMax, int WaitDelay);
        ~ParticleEmitter();

        void Update(float X, float Y);

        void AddColor(int Red, int Green, int Blue);

        std::vector<Particle> GetParticles();

    protected:
        std::vector<Particle> Particles;
        std::vector<SDL_Color> Colors;
        int Max;
        int XMax, XMin, YMax, YMin;
        int LMax, LMin;
        float SMin, SMax;
        int Delay, LogicalDelay, StartTime;
};

#endif // PARTICLEEMITTER_H
