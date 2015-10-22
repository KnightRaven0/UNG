#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int MaxParticles, int MaxSizeX, int MinSizeX, int MaxSizeY, int MinSizeY, float MaxSpeed, int MinSpeed, int LifeMin, int LifeMax) : ParticleEmitterTimer((LifeMin + LifeMax) / (MaxParticles * 2)){
    Particles.reserve(MaxParticles);
    Max = MaxParticles;
    XMax = MaxSizeX;
    XMin = MinSizeX;
    YMax = MaxSizeY;
    YMin = MinSizeY;
    SMax = MaxSpeed;
    SMin = MinSpeed;
    LMax = LifeMax;
    LMin = LifeMin;
}
ParticleEmitter::~ParticleEmitter(){
}
void ParticleEmitter::AddColor(Uint8 Red, Uint8 Green, Uint8 Blue){
    SDL_Color C = {Red, Green, Blue};
    Colors.emplace_back(C);
}

std::vector<Particle> ParticleEmitter::GetParticles(){
    return Particles;
}

void ParticleEmitter::Update(float X, float Y){
    int Size = Particles.size();
    if (ParticleEmitterTimer.IsTime()){
        int CSize = Colors.size();
        if (CSize == 0)
            return;
        if (Size != Max){
            int CP = rand() % CSize;
            double Angle = rand() % 360;
            float Speed = (rand() / (RAND_MAX / (SMax-SMin))) + SMin;
            float SpeedX = sin(Angle * PI / 180) * Speed;
            float SpeedY = cos(Angle * PI / 180) * Speed;
            Particles.push_back(Particle(X, Y, rand() % (XMax - XMin) + XMin, rand() % (YMax - YMin) + YMin, SpeedX, SpeedY, rand() % (LMax - LMin) + LMin, Colors[CP]));
        }
    }
    for (int p = Size - 1; p >= 0; p--){
        Particles[p].Update();
        if (Particles[p].GetLife() <= 0){
            Particles.erase(Particles.begin() + p);
        }
    }
}
