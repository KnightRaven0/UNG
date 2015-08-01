#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Renderer.h"

Renderer::Renderer(std::string Name, int PosX, int PosY, int ScreenWidth, int ScreenHeight){
	Window = SDL_CreateWindow(Name.c_str(), PosX, PosY, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	Render = SDL_CreateRenderer(Window, 0, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(Render, 0x00, 0x00, 0xFF, 0x00 );
    Camera.x = 0;
    Camera.y = 0;
}
Renderer::~Renderer(){
    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(Window);
    Paths.clear();
    Textures.clear();
    Camera.~SDL_Point();
}

void Renderer::RenderStart(){
    SDL_SetRenderDrawColor(Render, 0, 0, 255, 255);
    SDL_RenderClear(Render);
}
void Renderer::RenderFinish(){
    SDL_RenderPresent(Render);
}
SDL_Texture* Renderer::LoadTexture(const std::string &Path){
	SDL_Texture* NewTexture = IMG_LoadTexture(Render, Path.c_str());
	return NewTexture;
}
SDL_Texture* Renderer::GetTexture(const std::string &Path){
    for (int i = 0; i < Paths.size(); i++){
        if (Path == Paths[i])
            return Textures[i];
    }
    Textures.push_back(LoadTexture(Path));
    Paths.push_back(Path);
    return Textures[Textures.size() - 1];
}
SDL_Rect* Renderer::CameraShift(SDL_Rect* TranslatedObj){
        TranslatedObj->x -= Camera.x;
        TranslatedObj->y -= Camera.y;
        return TranslatedObj;
}

void Renderer::RenderObj(SDL_Texture *Texture, SDL_Renderer *Renderer, SDL_Rect *Destination, SDL_Rect *Cliping, double Angle, SDL_Point* Orgin){
	SDL_RenderCopyEx(Renderer, Texture, Cliping, Destination, Angle, Orgin, SDL_FLIP_NONE);
}
void Renderer::RenderParticles(std::vector<Particle> Particles){
    int Size = Particles.size();
    if (Size == 0)
        return;
    for (int i = 0; i < Size; i++){
        SDL_SetRenderDrawColor(Render, Particles[i].GetColor().r, Particles[i].GetColor().g, Particles[i].GetColor().b, 255);
        SDL_RenderFillRect(Render, Particles[i].GetDest());
    }
}
void Renderer::RenderSprites(std::vector<Sprite> Sprites){
    int Size = Sprites.size();
    if (Size == 0)
        return;
    for (int i = 0; i < Size; i++){
            RenderSprite(Sprites[i]);
    }
}
void Renderer::RenderSprite(Sprite _Sprite){
		RenderObj(_Sprite.GetTexture(), Render, CameraShift(_Sprite.GetDestination()), _Sprite.GetCliping(), _Sprite.GetAngle(), _Sprite.GetOrgin());
}
void Renderer::RenderAnims(std::vector<AnimatedSprite> Animations){
    int Size = Animations.size();
    for (int i = 0; i < Size; i++){
            Animations[i].GetTexture();
    Animations[i].GetCliping();
    Animations[i].GetAngle();
    Animations[i].GetOrgin();
    Animations[i].GetDestination();
        RenderObj(Animations[i].GetTexture(), Render, Animations[i].GetDestination(), Animations[i].GetCliping(), Animations[i].GetAngle(), Animations[i].GetOrgin());
    }
}

void Renderer::SetX(int NewX){
    int OldY;
    SDL_GetWindowPosition(Window, NULL, &OldY);
    SDL_SetWindowPosition(Window, NewX, OldY);
}
void Renderer::SetY(int NewY){
    int OldX;
    SDL_GetWindowPosition(Window, &OldX, NULL);
    SDL_SetWindowPosition(Window, OldX, NewY);
}
int Renderer::GetX(){
    int CurrentX;
    SDL_GetWindowPosition(Window, &CurrentX, NULL);
    return CurrentX;
}
int Renderer::GetY(){
    int CurrentY;
    SDL_GetWindowPosition(Window, NULL, &CurrentY);
    return CurrentY;
}

void Renderer::SetHeight(int NewHeight){
    int OldWidth;
    SDL_GetWindowSize(Window, &OldWidth, NULL);
    SDL_SetWindowSize(Window, OldWidth, NewHeight);
}
void Renderer::SetWidth(int NewWidth){
    int OldHeight;
    SDL_GetWindowSize(Window, NULL, &OldHeight);
    SDL_SetWindowSize(Window, NewWidth, OldHeight);
}
int Renderer::GetHeight(){
    int CurrentHeight;
    SDL_GetWindowSize(Window, NULL, &CurrentHeight);
    return CurrentHeight;
}
int Renderer::GetWidth(){
    int CurrentWidth;
    SDL_GetWindowSize(Window, &CurrentWidth, NULL);
    return CurrentWidth;
}
