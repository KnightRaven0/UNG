#include "Item.h"

Item::Item(SDL_Texture* Texture, SDL_Texture* IconTex) : IconTexure(IconTex) , ItemTexture(Texture){

}

Item::~Item(){

}

SDL_Texture* Item::GetIconTex(){
    return IconTexture;
}
SDL_Texture* Item::GetTex(){
    return ItemTexture;
}
std::string Item::GetName(){
    return Name;
}
