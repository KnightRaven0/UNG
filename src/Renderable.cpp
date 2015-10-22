#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Renderable.h"

Renderable::Renderable(SDL_Texture* RenderTexture, float PositionX, float PositionY) : Vector2(PositionX, PositionY){
    Visible = true;
    DestinationRect.x = GetIntX();
    DestinationRect.y = GetIntY();
    Texture = RenderTexture;
	UpdateDestination();
}
SDL_Rect* Renderable::GetDestination(){
    DestinationRect.x = x;
    DestinationRect.y = y;
    SDL_Rect* DestPointer = new SDL_Rect(DestinationRect);
    return DestPointer;
}
void Renderable::UpdateDestination(){SDL_QueryTexture(Texture, NULL, NULL, &DestinationRect.w, &DestinationRect.h);}
SDL_Texture* Renderable::GetTexture(){return Texture;}
void Renderable::SetTexture(SDL_Texture* NewTexture){Texture = NewTexture;}
void Renderable::SetDestinationSize(int W, int H){
    DestinationRect.h = H;
    DestinationRect.w = W;
}
