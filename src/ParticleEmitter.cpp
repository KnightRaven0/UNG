#include <SDL.h>
#include <stdlib.h>
#include <math.h>

#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int MaxParticles, int MaxSizeX, int MinSizeX, int MaxSizeY, int MinSizeY,
                        float MaxSpeed, int MinSpeed, int LifeMin, int LifeMax, int WaitDelay){
    Max = MaxParticles;
    XMax = MaxSizeX;
    XMin = MinSizeX;
    YMax = MaxSizeY;
    YMin = MinSizeY;
    SMax = MaxSpeed;
    SMin = MinSpeed;
    LMax = LifeMax;
    LMin = LifeMin;
    Delay = WaitDelay;
    LogicalDelay = WaitDelay;
    StartTime = SDL_GetTicks();
}

ParticleEmitter::~ParticleEmitter(){
    Particles.clear();
    Colors.clear();
}

void ParticleEmitter::AddColor(int Red, int Green, int Blue){
    SDL_Color C = {Red, Green, Blue};
    Colors.push_back(C);
}

std::vector<Particle> ParticleEmitter::GetParticles(){
    return Particles;
}

void ParticleEmitter::Update(float X, float Y){
    int Size = Particles.size();
    int CSize = Colors.size();
    if (CSize == 0)
        return;
    if (SDL_GetTicks() - StartTime > LogicalDelay){
        LogicalDelay += Delay;
        if (Size != Max){
            int CP = rand() % CSize;
            double Angle = rand() % 360;
            float Speed = (rand() / (RAND_MAX / (SMax-SMin))) + SMin;
            float SpeedX = sin(Angle * PI / 180) * Speed;
            float SpeedY = cos(Angle * PI / 180) * Speed;
            Particles.push_back(Particle(X, Y, rand() % (XMax - XMin) + XMin, rand() % (YMax - YMin) + YMin, SpeedX, SpeedY, rand() % (LMax - LMin) + LMin, Colors[CP]));
        }
    }
        for (int p = 0; p < Size; p++){
            Particles[p].Update();
            if (Particles[p].GetLife() <= 0)
                Particles.erase(Particles.begin() + p - 1);
        }
}
