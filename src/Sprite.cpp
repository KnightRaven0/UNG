#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Sprite.h"

Sprite::Sprite(SDL_Texture* SpriteTexture, float PosX, float PosY) : Renderable(SpriteTexture, PosX, PosY){
	UpdateDestination();
	Origin.x = DestinationRect.w / 2;
	Origin.y = DestinationRect.h / 2;
	Angle = 0;
	Scale = 1;
	ClipingRect.x = -1;
	ClipingRect.y = -1;
	ClipingRect.w = -1;
	ClipingRect.h = -1;
}
Sprite::~Sprite(){}

//Getters
int Sprite::GetHeight(){return DestinationRect.h;}
int Sprite::GetWidth(){return DestinationRect.w;}
double Sprite::GetAngle(){return Angle;}
SDL_Point* Sprite::GetOrigin(){
    SDL_Point Point;
    Point.x = Origin.x * Scale;
    Point.y = Origin.y * Scale;
    SDL_Point* OriginPointer = new SDL_Point(Point);
    return OriginPointer;
}
SDL_Rect* Sprite::GetDestination(){
    DestinationRect.x = GetIntX();
    DestinationRect.y = GetIntY();
    SDL_Rect* DestPointer = new SDL_Rect(DestinationRect);
    DestPointer->h = DestPointer->h * Scale;
    DestPointer->w = DestPointer->w * Scale;
    return DestPointer;
}
SDL_Rect* Sprite::GetCliping(){
    if (ClipingRect.x == -1 && ClipingRect.y == -1 && ClipingRect.h == -1 && ClipingRect.w == -1)
        return NULL;
    else{
        SDL_Rect* ClipPointer = new SDL_Rect(ClipingRect);
        return ClipPointer;
    }
}

//Setters
void Sprite::SetAngle(double NewAngle){Angle = NewAngle;}
void Sprite::ScaleScale(float ScalesScale){Scale = Scale * ScalesScale;}
void Sprite::SetScale(float NewScale){Scale = NewScale;}
void Sprite::SetOrigin(int OriginX, int OriginY){Origin.x = OriginX; Origin.y = OriginY;}
void Sprite::SetCliping(int ClipX, int ClipY, int ClipW, int ClipH){
    ClipingRect.x = ClipX;
    ClipingRect.y = ClipY;
    ClipingRect.h = ClipH;
    ClipingRect.w = ClipW;
}
