#include <SDL.h>

#include "Particle.h"
#include "Vector2.h"

Particle::Particle(int X, int Y, int SizeX, int SizeY, float SpeedX, float SpeedY, int LifeTime, SDL_Color ParticleColor) : Pos(X, Y){
    StartTime = SDL_GetTicks();
    Height = SizeY;
    Width = SizeX;
    DeltaX = SpeedX / 100;
    DeltaY = SpeedY / 100;
    Color = ParticleColor;
    Life = LifeTime;
    LogicalDelay = 10;
}
SDL_Color Particle::GetColor(){return Color;}
SDL_Rect* Particle::GetDest(){
    SDL_Rect R;
    R.h = Height;
    R.w = Width;
    R.x = Pos.GetX();
    R.y = Pos.GetY();
    SDL_Rect* P = new SDL_Rect(R);
    return P;
}
int Particle::GetLife(){return Life;}
void Particle::Update(){
    if (SDL_GetTicks() - StartTime > LogicalDelay){
        LogicalDelay += 10;
        Life -= 10;
        Pos.SetX(Pos.GetX() + DeltaX);
        Pos.SetY(Pos.GetY() + DeltaY);
    }
}
