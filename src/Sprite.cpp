#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Renderable.h"
#include "Sprite.h"

Sprite::Sprite(SDL_Texture* SpriteTexture, float PosX, float PosY) : Renderable(SpriteTexture, PosX, PosY){
	UpdateDestination();

	Orgin.x = DestinationRect.w / 2;
	Orgin.y = DestinationRect.h / 2;
	Angle = 0;
	Scale = 1;
	ClipingRect.x = -1;
	ClipingRect.y = -1;
	ClipingRect.w = -1;
	ClipingRect.h = -1;
}

Sprite::~Sprite(){
}

inline void Sprite::UpdateDestination(){
	SDL_QueryTexture(Texture, NULL, NULL, &DestinationRect.h, &DestinationRect.w);
}

//Getters
int Sprite::GetHeight(){return DestinationRect.h;}
int Sprite::GetWidth(){return DestinationRect.w;}
double Sprite::GetAngle(){return Angle;}
SDL_Point* Sprite::GetOrgin(){
    SDL_Point Point;
    Point.x = Orgin.x * Scale;
    Point.y = Orgin.y * Scale;
    SDL_Point* OrginPointer = new SDL_Point(Point);
    return OrginPointer;
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
void Sprite::SetOrgin(int OrginX, int OrginY){Orgin.x = OrginX; Orgin.y = OrginY;}
void Sprite::SetCliping(int ClipX, int ClipY, int ClipH, int ClipW){
	ClipingRect.x = ClipX;
	ClipingRect.y = ClipY;
	ClipingRect.h = ClipH;
	ClipingRect.w = ClipW;
}
