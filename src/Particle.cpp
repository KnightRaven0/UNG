#include <SDL.h>

#include "Particle.h"
#include "Vector2.h"

Particle::Particle(int X, int Y, int SizeX, int SizeY, float SpeedX, float SpeedY, int LifeTime, SDL_Color ParticleColor) : Vector2(X, Y), ParticleTimer(10){
    Height = SizeY;
    Width = SizeX;
    DeltaX = SpeedX / 100;
    DeltaY = SpeedY / 100;
    Color = ParticleColor;
    Life = LifeTime;
}
Particle::~Particle(){

}
SDL_Color Particle::GetColor(){return Color;}
SDL_Rect* Particle::GetDest(){
    SDL_Rect R;
    R.h = Height;
    R.w = Width;
    R.x = GetX();
    R.y = GetY();
    SDL_Rect* P = new SDL_Rect(R);
    return P;
}
int Particle::GetLife(){return Life;}
void Particle::Update(){
    if (ParticleTimer.IsTime()){
        Life -= 10;
        SetX(GetX() + DeltaX);
        SetY(GetY() + DeltaY);
    }
}
